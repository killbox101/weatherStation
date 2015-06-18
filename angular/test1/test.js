
// Code goes here

var myApp = angular.module("myApp", ['n3-line-chart'])
		.controller('weatherController', function($scope, $http) 
		{
    
			//$http({method:'GET',url:'http://192.168.2.10:5000/weatherToday/'})
			$http({method:'GET',url:'http://192.168.2.10:5000/wmd/2'})
			.success(function(data)

			{
			 
			$scope.wRecord = data.items; // response data
			//alert($scope.wRecord)
		    $scope.options = {
		      axes: {
    					y: {min: 12}
    				  },
			  series: [
			    {
			      y: "DHTCelcius",
			      label: "DHT Celcius",
			      color: "#ff7f0e",
			      type: "area"
			    },
			    {
			      y: "BaroCelcius",
			      label: "Baro Celcius",
			      color: "#1f77b4",
			      type: "area",
			      visible: "false"
			    }
			  ],
			  tooltip: {mode: 'scrubber', formatter: function(x, y, series) {return 'pouet';}}
			}; //function
		}); //weatherController
}); //app 
