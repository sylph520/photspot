<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8"/>
    <title>Bubble</title>
	<style>
	.left {
	 float:left;
	}
	.right {
	 float:right;
	}
	#popupMsg{
		display: none; 
		position: absolute; 
		}
	</style>
  </head>

  <body>
  <div width="1500px">
	  <div id="popupMsg" class="right"  height=300px; width=350px;></div>
	  <div id="chart" class="left"></div>
  </div>
    <script src="js/datav.js"></script>
    <script src="js/axis.js"></script>
	<script src="js/jscharts.js"></script>
    <script src="js/bubble.js"></script>
    <script>  
		datapath = "VisualData\\4e22a064f4d2cf03ff76fcb351ab2cd0\\nations2.csv";
		var bubble = new Bubble("chart", {"width": 800, "height": 600});
		DataV.csv(datapath, function(dataSource) {bubble.setSource(dataSource); bubble.render();});
    </script>
	

  </body>
</html>
