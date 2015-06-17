
// Code goes here

var myApp = angular.module("myApp", [])
		.controller('weatherController', function($scope, $http) 
		{
        
			$scope.status="Hello ";
	  		
			$http({method:'GET',url:'http://192.168.2.10:5000/weatherToday/'})
			.success(function(data)

			{
			 
			$scope.wRecord = data.items; // response data
			//alert($scope.wRecord)
			
			});
		
		}); 
