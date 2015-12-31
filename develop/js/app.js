angular.module('myApp', [ 'ngCsvImport', 'chart.js' ])
	.controller('mainCtrl', function($scope) {
		$scope.settings = {
			animation: false,
			pointDot: false,
			showTooltips: false,
		}
		$scope.$watch('csv', function() {
			console.log($scope.csv);
			try {
				$scope.series = [ "total" ];
				$scope.labels = [];
				$scope.data = [ [] ];
				for(var i = 0; i < $scope.csv.result.length; ++i) {
					console.log($scope.labels);
					$scope.data[0].push($scope.csv.result[i]["1"]);
					if(i % 50 == 0)
						$scope.labels.push(i);
					else
						$scope.labels.push("");
				}
			}
			catch(e) {
				// console.log(e);
			}
		}, true);
	})