//var app = angular.module("weatherStation", [])
//app.controller("wsController", function ($scope,$http){
//
//	$http({method:'GET',url:'http:192.168.2.10:5000/weatherToday/'})
////$http({method:'GET', url:'http://movieapp-sitepointdemos.rhcloud.com/api/movies'}).success(function(data)
//    success(function(data) {
//    $scope.weather = data;
//	});
//


// Code goes here

var myApp = angular.module("myApp", [])
		.controller('LabController', function($scope, $http) {
        
		$scope.status="Hello ";
  // http://www.listingsearch.com/service/test_function  please check its returns one onject 
  
		//$http({method:'GET', url:'http://movieapp-sitepointdemos.rhcloud.com/api/movies'})
			$http({method:'GET',url:'http://192.168.2.10:5000/weatherToday/'}).success(function(data)
{
 
//alert($scope.posts);
 
$scope.movies = data; // response data
//alert($scope.movies); 
});

		
		
		
		/*$scope.batches = [
			{id: "2014BATCH50", status: "QC in Progress. Illumina: 24/50",  date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"},
			{id: "2014BATCH49", status: "Pre-Extraction",  date: "10/24/14", date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"},
			{id: "2014BATCH48", status: "Awaiting Raw Uploads", date: "10/24/14", date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"},
			{id: "2014BATCH47", status: "Pre-Extraction", date: "10/24/14", date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"},
			{id: "2014BATCH46", status: "Awaiting Raw & Modified Uploads", date: "10/24/14", date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"},
			{id: "2014BATCH46", status: "Awaiting Raw & Modified Uploads", date: "10/24/14", date: "10/24/14", qlty: "check", illumina: "none, raw, modified, modified", FX: "modified"}
		];*/
		
	}); 
