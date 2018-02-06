var myAPI = "8B18mZhs2uqttEfDJ95xx7PTk8bohh7n";
var serverURL = "http://http://localhost:8080/";
var mlabURL = "https://api.mlab.com/api/1";
var getURL = "/databases/convodb/collections";
var textURL = "/getDataText";
var AnalysisURL = "/getDataAnalysis";

var xhr = new XMLHttpRequest();
xhr.open('GET', serverURL+textURL, true);
xhr.send();
console.log(xhr.getAllResponseHeaders());
