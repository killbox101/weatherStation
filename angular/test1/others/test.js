
// Code goes here

var myApp = angular.module("myApp", ['n3-line-chart']);


myApp.controller('weatherController',function($scope, $http) 
{

	$http({method:'GET',url:'http://192.168.2.10:5000/weatherToday/'})
	//$http({method:'GET',url:'http://192.168.2.10:5000/wmd/27'})
	//$http({method:'GET',url:'http://192.168.2.10:5000/wmd/2'})
	.success(function(data)

	{
	 
		$scope.wRecord = data.items; // response data
		//$scope.name = data.name	
		//alert($scope.wRecord)
	    $scope.options = {
	    	tooltip: {mode: 'scrubber'},
	        axes: {
					y: {min: 12}
					//x: {key:'DateRecorded', type:'date'}
				  },
		    series: [
		    {
		      y: "DHTCelcius",
		      label: "DHT Celcius",
		      color: "#ff7f0e",
		      type: "area"
		    }
		//    {
		//      y: "BaroCelcius",
		//      label: "Baro Celcius",
		//      color: "#1f77b4",
		//      type: "area",
		//      visible: "true"
		//    }
		  ]
		  
		  //tooltip: {mode: 'scrubber', formatter: function(x, y, series) {return 'pouet';}}
		  };

	}) //function

	.error(function(data)
	{

		$scope.wsRecord =[ 
					 {
					    x: 0,
					    val_0: 0,
					    val_1: 0,
					    val_2: 0,
					    val_3: 0
					  },
					  {
					    x: 7,
					    val_0: 4.927,
					    val_1: 3.35,
					    val_2: -13.074,
					    val_3: -12.625
					  }];
	});
			
});




myApp.controller('weatherController2',function($scope, $http) 
{


	$http({method:'GET',url:'http://192.168.2.10:5000/wmd/2'})
	.success(function(data)

	{
	 
		$scope.wRecord = data.items; // response data
		//alert($scope.wRecord)
	    $scope.options = {
	    	tooltip: {mode: 'scrubber'},
	        //axes: {
			//		y: {min: 12}
			//	  },
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
		      visible: "true"
		    }
		  ]
		  
		  //tooltip: {mode: 'scrubber', formatter: function(x, y, series) {return 'pouet';}}
		  };

	}) //function

	.error(function(data)
	{

		$scope.wsRecord =[ 
					 {
					    x: 0,
					    val_0: 0,
					    val_1: 0,
					    val_2: 0,
					    val_3: 0
					  },
					  {
					    x: 7,
					    val_0: 4.927,
					    val_1: 3.35,
					    val_2: -13.074,
					    val_3: -12.625
					  }];
	});
			
});


myApp.controller('weatherControllerPressure',function($scope, $http) 
{

	$http({method:'GET',url:'http://192.168.2.10:5000/weatherToday/'})
	//$http({method:'GET',url:'http://192.168.2.10:5000/wmd/27'})
	//$http({method:'GET',url:'http://192.168.2.10:5000/wmd/2'})
	.success(function(data)

	{
		$scope.wRecord = data.items; // response data
		//alert($scope.wRecord)
	    $scope.options = 
	    {
	    	tooltip: {mode: 'scrubber'},
	        //axes: {
			//		y: {min: 12}
			//	  },
		    series: [
		    {
		      y: "BaroPressure",
		      label: "DHT Celcius",
		      color: "#ff7f0e",
		      type: "area"
		    }]
		  
	  	};

	}) //function

	.error(function(data)
	{

		$scope.wsRecord =[ 
					 {
					    x: 0,
					    val_0: 0,
					    val_1: 0,
					    val_2: 0,
					    val_3: 0
					  },
					  {
					    x: 7,
					    val_0: 4.927,
					    val_1: 3.35,
					    val_2: -13.074,
					    val_3: -12.625
					  }];
	});
			
});


myApp.controller('weatherControllerMinMaxCurrentTemp', function($scope,$http)
{
 $http({method:'GET',url:'http://192.168.2.10:5000/currentMinMaxTemp/'})
 .success(function(data)
 	{
 		$scope.wRecord = data.items;
 	
 	})
 	.error(function(data)
 	{
 		$scope.wRecord = 'Shits broken yo!'
 	});

});


//myApp.controller('weatherControllerMinMaxCurrentTemp', function($scope,$http,$interval)
//{
// var c=0;
// $interval(function(){
// 	 $http({method:'GET',url:'http://192.168.2.10:5000/currentMinMaxTemp/'})
// .success(function(data)
// 	{
// 		$scope.wRecord = data.items;
// 	
// 	})
// 	.error(function(data)
// 	{
// 		$scope.wRecord = 'Shits broken yo!'
// 	});
//
//  $alert("This message has refreshed"+c+"time");
//
//
// },1000);
//
//});