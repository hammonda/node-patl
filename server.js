var http = require('http');
var querystring = require('querystring');
var url = require('url');

var patl = new (require('./build/Release/nodepatl').Patl);

// Example Usage: http://localhost:8080/?word=responsiblity&dist=3

var ERROR_MSG = { error: 'Invalid query string' };
var PORT = process.argv.length > 2 ? Number(process.argv[2]) : 8080;

// Prepare an array of dictionary names to load.
var sizes = [10,20,35,40,50,55,60,70];
var dictionaries = [];
for (var i in sizes) {
  dictionaries.push('scowl/english-words.'+sizes[i]);
  dictionaries.push('scowl/british-words.'+sizes[i]);
}

// Load Dictionaries (asynchronous).
patl.loadDictionary(dictionaries, function (err, size) {
  if (!err) {
    console.log('Dictionary Size', size);
    createServer(); 
  } else {
    console.error(err);
  }
});

// Create the HTTP JSON server.
function createServer () {
  http.createServer(function (request, response) {
    var parse = url.parse(request.url);
    var queryObj = querystring.parse(parse.query);
    if ('word' in queryObj) {
      var dist = (queryObj.dist === undefined)  ? 2 : Number(queryObj.dist);
      patl.searchDictionary(queryObj.word.toLowerCase(), dist, 
        function (results) {
          sendJSON(response, {
            results: results
          });
      });
    } else {
      sendJSON(response, ERROR_MSG);
    }
  }).listen(PORT);  
}

// Send JSON response.
function sendJSON (response, obj) {
  response.writeHead(200, {
    "Content-Type": "application/json;charset=utf-8"
  });
  response.write(JSON.stringify(obj, null, ' '));
  response.end();
}
