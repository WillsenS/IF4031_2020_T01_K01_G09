const http = require('http');
const fs = require('fs');

if (process.argv.length <= 2) {
    console.log("Please provide PORT and FILEPATH (example : 'node server_high.js 8080 dummy1.html')")
    return;
}

const argument = process.argv.slice(2);
console.log('[INFO] Starting server on port ' + argument[0]);
http.createServer(function (req, res) {
    fs.readFile(argument[1], (err, data) => {
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        return res.end();
    });
}).listen(argument[0]);

console.log('[INFO] Server running on port ' + argument[0]);