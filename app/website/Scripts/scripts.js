var myAPI = "8B18mZhs2uqttEfDJ95xx7PTk8bohh7n";
var serverURL = "http://localhost:8080/";
var mlabURL = "https://api.mlab.com/api/1";
var getURL = "/databases/convodb/collections";
var textURL = "getDataText";
var AnalysisURL = "getDataAnalysis";

var xhr = $.get({
  url: serverURL + AnalysisURL,
  success: function(){
    console.log("It worked!");
  }
});

console.log("Status:");
console.log(xhr.status);
console.log("Status Text:");
console.log(xhr.statusText);
console.log("Response Header:");
console.log(xhr.getAllResponseHeaders());
console.log("Response Text:");
console.log(xhr.responseText);
console.log(xhr);
