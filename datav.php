<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8"/>
	<script src="js/datav.js"></script>
    <script src="js/axis.js"></script>
	<script src="js/jscharts.js"></script>
    <script src="js/bubble.js"></script>
    <title>Bubble Graph</title>
	<style>
	.left {
		float:left;
	}
	.right {
		float:right;
		height:300px;
		width:350px;
	}
	#popupMsg{
		display: none; 
		position: absolute; 
		}
	</style>
  </head>
  <body>
		<div width="1500px">
			<div id="popupMsg" class="right"></div>
			<div id="chart" class="left"></div>
		</div>
		<script>  
			var datapath = "<? echo "$datavpath";?>";
			//datapath = "VisualData\\4466ab65196dc8dc7af6b0f291c346dd\\nations2.csv";
			var bubble = new Bubble("chart", {"width": 800, "height": 600});
			DataV.csv(datapath, function(dataSource) {bubble.setSource(dataSource); bubble.render();});
			
			//add by yangyang in 2013.3.20 for test
			//var bubble = new Bubble(¡°chart¡±, {¡°width¡±: 800, ¡°height¡±: 600}); 
			//DataV.csv("VisualData\\4466ab65196dc8dc7af6b0f291c346dd\\nations2.csv", function(dataSource) 
			//{     
				   // bubble.setSource(dataSource);
				   //bubble.chooseDimensions(["year", "country", "survival","children", "population", "region"]); 
				   //  bubble.render(); 
			//});
		</script>
  </body>
</html>
