#include <iostream>
#include <cstring>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>

#include <string>
#include <tuple>
#include <cstdint>

#define UNUSED(expr) do { (void)(expr); } while (0)

static char *filepath;

enum class URI_TO_PATH_STATUS : std::int8_t {
  SUCCESS = 0,
  FAILURE_URI_PARSE,
  FAILURE_URI_TO_PATH,
  FAILURE_PATH_DECODE,
};

std::tuple<std::string, URI_TO_PATH_STATUS> uri_to_path(const char *uri) {
  assert(uri != NULL);

  struct evhttp_uri *decodedUri = NULL;
  const char *path = NULL;
  const char *decodedPath = NULL;

  URI_TO_PATH_STATUS status = URI_TO_PATH_STATUS::SUCCESS;

  decodedUri = evhttp_uri_parse(uri);

  if (!decodedUri) {
    status = URI_TO_PATH_STATUS::FAILURE_URI_PARSE;
    goto end;
  }

  path = evhttp_uri_get_path(decodedUri);

  if (!path) {
    status = URI_TO_PATH_STATUS::FAILURE_URI_TO_PATH;
    goto end;
  }

  decodedPath = evhttp_uridecode(path, 0, NULL);

  if (!decodedPath) {
    status = URI_TO_PATH_STATUS::FAILURE_PATH_DECODE;
    goto end;
  }

end:
  if (decodedUri) {
    evhttp_uri_free(decodedUri);
  }

  auto result = std::make_tuple(
      (status == URI_TO_PATH_STATUS::SUCCESS ? std::string(decodedPath) : std::string("")),
      status
                         );

  free((void *)decodedPath);

  return result;
}

static void handle_file(struct evhttp_request *req, void *arg)
{
  UNUSED(arg);

  const char *uri = evhttp_request_get_uri(req);

  // only GET requests allowed
  if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
    evhttp_send_error(req, HTTP_BADREQUEST, 0);
    return;
  }
  auto result = uri_to_path(uri);
  auto status = std::get<1>(result);

  assert(status == URI_TO_PATH_STATUS::SUCCESS);

  struct evbuffer *evb = NULL;
  evb = evbuffer_new();
  char fullpath[1000];
  strcpy(fullpath,"../");
  strcat(fullpath, filepath);
  std::cout << "path: " << fullpath << std::endl;
  int fd = -1;
  if ((fd = open(fullpath, O_RDONLY)) < 0) {
    goto notFound;
  }
  struct stat st;
  if (fstat(fd, &st) < 0) {
    goto notFound;
  }
  evbuffer_add_file(evb, fd, 0, st.st_size);
  evhttp_send_reply(req, 200, "OK", evb);
  evbuffer_free(evb);
  notFound:
    evhttp_send_error(req, HTTP_NOTFOUND, 0);
}

int main(int argc, char **argv)
{
  UNUSED(argc);

  struct event_base *base;
  struct evhttp *http;
  struct evhttp_bound_socket *handle;

  if (argc <= 1) {
      std::cerr << "Please provide PORT and FILEPATH (example : './webserver 8080 dummy1.html')" << std::endl;
      return 1;
  }

  const ev_uint16_t port = (unsigned short) std::strtoul(argv[1], NULL, 0);
  const char *host = "0.0.0.0";
  filepath = argv[2];

  base = event_base_new();

  if (!base) {
    std::cerr << "FAILURE: Couldn't create an event_base." << std::endl;
    return 1;
  }

  http = evhttp_new(base);

  if (!http) {
    std::cerr << "FAILURE: Couldn't create an evhttp." << std::endl;
    return 1;
  }

  // register catchall handler
  evhttp_set_gencb(http, handle_file, argv[3]);
  handle = evhttp_bind_socket_with_handle(http, host, port);

  if (!handle) {
    std::cerr << "FAILURE: Couldn't bind to " << host << ":" << port << std::endl;
    return 1;
  }

  event_base_dispatch(base);

  return 0;
}
