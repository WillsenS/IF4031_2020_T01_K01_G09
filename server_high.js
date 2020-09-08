const http = require('http');
const fs = require('fs');

console.log('[INFO] Starting server on port 8080...')

http.createServer(function (req, res) {
    switch(req.url){
        case '/dummy1':
            fs.readFile('dummy_file/dummy1.html', (err, data) => {
                res.writeHead(200, {'Content-Type': 'text/html'});
                res.write(data);
                return res.end();
            });
            break;
        case '/dummy2':
            fs.readFile('dummy_file/dummy2.html', (err, data) => {
                res.writeHead(200, {'Content-Type': 'text/html'});
                res.write(data);
                return res.end();
            });
            break;
        default:
            
            res.writeHead(200, {'Content-Type': 'text/plain'});
            res.end('Please choose between /dummy1 and /dummy 2 ..!');
            return res.end();
    }
}).listen(8080);

console.log('[INFO] Server running on port 8080')