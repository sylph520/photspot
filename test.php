
<html> 
<head>	
	<title></title> 

	<script type="text/javascript"> 
	if(location.hostname.toLowerCase().indexOf('dhtmlgoodies') >=0) {
	  var _gaq = _gaq || [];
	  _gaq.push(['_setAccount', 'UA-2042963-3']);
	  _gaq.push(['_trackPageview']);
	 
	  (function() {
		var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
		ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
		var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	  })();
	}
	</script> 
	
	<style type="text/css"> 
	html{
		height:100%;
	}
	body{	
		height:100%;
		margin:0px;
		padding:0px;
		font-family: Trebuchet MS, Lucida Sans Unicode, Arial, sans-serif;
	}
	#pageContent{
		width:950px;
	}
	.ad{
		margin-top:120px;
	}
	h1{
		font-size:0.9em;
	}
 
	a{
		color:red;
	}
	/* Entire pane */
	
	#dhtmlgoodies_xpPane{
		
		float:left;
		height:1200px;
		width:900;
	}
	#dhtmlgoodies_xpPane .dhtmlgoodies_panel{
		margin-left:10px;
		margin-right:10px;
		margin-top:10px;	
	}
	#dhtmlgoodies_xpPane .panelContent{
		font-size:0.7em;
		background-position:top right;
		background-repeat:repeat-y;
		border-left:1px solid #FFF;
		border-bottom:1px solid #FFF;	
		padding-left:2px;
		padding-right:2px;	
		overflow:hidden;
		position:relative;
		clear:both;
	}
	#dhtmlgoodies_xpPane .panelContent div{
		position:relative;
	}
	#dhtmlgoodies_xpPane .dhtmlgoodies_panel .topBar{
		background-image:url('images/bg_panel_top_right.gif');
		background-repeat:repeat-x;
		background-position:top right;
		height:25px;
		padding-right:5px;
		cursor:pointer;
		overflow:hidden;		
 
	}
	#dhtmlgoodies_xpPane .dhtmlgoodies_panel .topBar span{
		line-height:25px;
		vertical-align:middle;
		font-family:arial;
		font-size:0.7em;
		color:#215DC6;
		font-weight:bold;
		float:left;
		padding-left:5px;
	}
	#dhtmlgoodies_xpPane .dhtmlgoodies_panel .topBar img{
		float:right;
		cursor:pointer;
	}
	#otherContent{	/* Normal text content */
		float:left;	/* Firefox - to avoid blank white space above panel */
		padding-left:10px;	/* A little space at the left */
	}
	</style> 
	<script type="text/javascript"> 
	/************************************************************************************************************
	(C) www.dhtmlgoodies.com, October 2005
	
	This is a script from www.dhtmlgoodies.com. You will find this and a lot of other scripts at our website.	
	
	Terms of use:
	You are free to use this script as long as the copyright message is kept intact. However, you may not
	redistribute, sell or repost it without our permission.
	
	Updated:
	
	February, 22nd 2006 - Instead of skipping onclick events when slide is in progress, start sliding in the other direction if mouse is clicked the second time.
	April, 	23rd 2006 - Added support for having only one pane expanded simultaneously( xpPanel_onlyOneExpandedPane)
	Thank you!
	
	www.dhtmlgoodies.com
	Alf Magne Kalleland
	
	************************************************************************************************************/	
 
	/* Update LOG 
	
	January, 28th - Fixed problem when double clicking on a pane(i.e. expanding and collapsing).
	
	*/
	var xpPanel_slideActive = true;	// Slide down/up active?
	var xpPanel_slideSpeed = 20;	// Speed of slide
	var xpPanel_onlyOneExpandedPane = false;	// Only one pane expanded at a time ?
	
	var dhtmlgoodies_xpPane;
	var dhtmlgoodies_paneIndex;
	
	var savedActivePane = false;
	var savedActiveSub = false;
 
	var xpPanel_currentDirection = new Array();
	var cookieNames = new Array();
	var currentlyExpandedPane = false;
	
	/*
	These cookie functions are downloaded from 
	http://www.mach5.com/support/analyzer/manual/html/General/CookiesJavaScript.htm
	*/	
	function Get_Cookie(name) { 
	   var start = document.cookie.indexOf(name+"="); 
	   var len = start+name.length+1; 
	   if ((!start) && (name != document.cookie.substring(0,name.length))) return null; 
	   if (start == -1) return null; 
	   var end = document.cookie.indexOf(";",len); 
	   if (end == -1) end = document.cookie.length; 
	   return unescape(document.cookie.substring(len,end)); 
	} 
	// This function has been slightly modified
	function Set_Cookie(name,value,expires,path,domain,secure) { 
		expires = expires * 60*60*24*1000;
		var today = new Date();
		var expires_date = new Date( today.getTime() + (expires) );
	    var cookieString = name + "=" +escape(value) + 
	       ( (expires) ? ";expires=" + expires_date.toGMTString() : "") + 
	       ( (path) ? ";path=" + path : "") + 
	       ( (domain) ? ";domain=" + domain : "") + 
	       ( (secure) ? ";secure" : ""); 
	    document.cookie = cookieString; 
	}
 
	function cancelXpWidgetEvent()
	{
		return false;	
		
	}
	
	function showHidePaneContent(e,inputObj)
	{
		if(!inputObj)inputObj = this;
		
		var img = inputObj.getElementsByTagName('IMG')[0];
		var numericId = img.id.replace(/[^0-9]/g,'');
		var obj = document.getElementById('paneContent' + numericId);
		if(img.src.toLowerCase().indexOf('up')>=0){
			currentlyExpandedPane = false;
			img.src = img.src.replace('up','down');
			if(xpPanel_slideActive){
				obj.style.display='block';
				xpPanel_currentDirection[obj.id] = (xpPanel_slideSpeed*-1);
				slidePane((xpPanel_slideSpeed*-1), obj.id);
			}else{
				obj.style.display='none';
			}
			if(cookieNames[numericId])Set_Cookie(cookieNames[numericId],'0',100000);
		}else{
			if(this){
				if(currentlyExpandedPane && xpPanel_onlyOneExpandedPane)showHidePaneContent(false,currentlyExpandedPane);
				currentlyExpandedPane = this;	
			}else{
				currentlyExpandedPane = false;
			}
			img.src = img.src.replace('down','up');
			if(xpPanel_slideActive){
				if(document.all){
					obj.style.display='block';
					//obj.style.height = '1px';
				}
				xpPanel_currentDirection[obj.id] = xpPanel_slideSpeed;
				slidePane(xpPanel_slideSpeed,obj.id);
			}else{
				obj.style.display='block';
				subDiv = obj.getElementsByTagName('DIV')[0];
				obj.style.height = subDiv.offsetHeight + 'px';
			}
			if(cookieNames[numericId])Set_Cookie(cookieNames[numericId],'1',100000);
		}	
		return true;	
	}
	
	function slidePane(slideValue,id)
	{
		if(slideValue!=xpPanel_currentDirection[id]){
			return false;
		}
		var activePane = document.getElementById(id);
		if(activePane==savedActivePane){
			var subDiv = savedActiveSub;
		}else{
			var subDiv = activePane.getElementsByTagName('DIV')[0];
		}
		savedActivePane = activePane;
		savedActiveSub = subDiv;
		
		var height = activePane.offsetHeight;
		var innerHeight = subDiv.offsetHeight;
		height+=slideValue;
		if(height<0)height=0;
		if(height>innerHeight)height = innerHeight;
		
		if(document.all){
			activePane.style.filter = 'alpha(opacity=' + Math.round((height / subDiv.offsetHeight)*100) + ')';
		}else{
			var opacity = (height / subDiv.offsetHeight);
			if(opacity==0)opacity=0.01;
			if(opacity==1)opacity = 0.99;
			activePane.style.opacity = opacity;
		}			
		
					
		if(slideValue<0){			
			activePane.style.height = height + 'px';
			subDiv.style.top = height - subDiv.offsetHeight + 'px';
			if(height>0){
				setTimeout('slidePane(' + slideValue + ',"' + id + '")',10);
			}else{
				if(document.all)activePane.style.display='none';
			}
		}else{			
			subDiv.style.top = height - subDiv.offsetHeight + 'px';
			activePane.style.height = height + 'px';
			if(height<innerHeight){
				setTimeout('slidePane(' + slideValue + ',"' + id + '")',10);				
			}		
		}
		
		
		
		
	}
	
	function mouseoverTopbar()
	{
		var img = this.getElementsByTagName('IMG')[0];
		var src = img.src;
		img.src = img.src.replace('.gif','_over.gif');
		
		var span = this.getElementsByTagName('SPAN')[0];
		span.style.color='#428EFF';		
		
	}
	function mouseoutTopbar()
	{
		var img = this.getElementsByTagName('IMG')[0];
		var src = img.src;
		img.src = img.src.replace('_over.gif','.gif');		
		
		var span = this.getElementsByTagName('SPAN')[0];
		span.style.color='';
	}
	
	function initDhtmlgoodies_xpPane(panelTitles,cookieArray)
	{
		dhtmlgoodies_xpPane = document.getElementById('dhtmlgoodies_xpPane');
		var divs = dhtmlgoodies_xpPane.getElementsByTagName('DIV');
		dhtmlgoodies_paneIndex=0;
		cookieNames = cookieArray;
		var panelDisplayed = new Array(divs.length);
		for(var no=0;no<divs.length;no++)
		{
			if(divs[no].className=='dhtmlgoodies_panel')
			{
				var outerContentDiv = document.createElement('DIV');	
				var contentDiv = divs[no].getElementsByTagName('DIV')[0];
				outerContentDiv.appendChild(contentDiv);	
			
				outerContentDiv.id = 'paneContent' + dhtmlgoodies_paneIndex;
				outerContentDiv.className = 'panelContent';
				var topBar = document.createElement('DIV');
				topBar.onselectstart = cancelXpWidgetEvent;
				var span = document.createElement('SPAN');				
				span.innerHTML = panelTitles[dhtmlgoodies_paneIndex];
				topBar.appendChild(span);
				topBar.onclick = showHidePaneContent;
				if(document.all)topBar.ondblclick = showHidePaneContent;
				topBar.onmouseover = mouseoverTopbar;
				topBar.onmouseout = mouseoutTopbar;
				topBar.style.position = 'relative';
 
				var img = document.createElement('IMG');
				img.id = 'showHideButton' + dhtmlgoodies_paneIndex;
				img.src = 'images/arrow_up.gif';				
				topBar.appendChild(img);
				
				if(cookieArray[dhtmlgoodies_paneIndex]){
					cookieValue = Get_Cookie(cookieArray[dhtmlgoodies_paneIndex]);
					if(cookieValue)panelDisplayed[dhtmlgoodies_paneIndex] = cookieValue==1?true:false;
					
				}
				
				if (no==0)
				{
					panelDisplayed[dhtmlgoodies_paneIndex] = true;
				}
				else
				{
					panelDisplayed[dhtmlgoodies_paneIndex] = false;
				}
				
				if(!panelDisplayed[dhtmlgoodies_paneIndex]){
					outerContentDiv.style.height = '0px';
					contentDiv.style.top = 0 - contentDiv.offsetHeight + 'px';
					if(document.all)outerContentDiv.style.display='none';
					img.src = 'images/arrow_down.gif';
				}
								
				topBar.className='topBar';
				divs[no].appendChild(topBar);				
				divs[no].appendChild(outerContentDiv);	
				dhtmlgoodies_paneIndex++;			
			}			
		}
	}
	
	</script> 

</head> 


<body> 

<div id="pageContent">
<!-- START OF PANE CODE --> 
	<div id="dhtmlgoodies_xpPane">
	
	
	
	
		<div class="dhtmlgoodies_panel"> 
				<div align="center">
				<iframe width="1000px" height="700px" src="datav.php?VisualData\\1565b959dbb894e12ef10fe3322819d8\\B23K.csv"></iframe>
				</div>

		</div>
		
		<div class="dhtmlgoodies_panel"> 
				<div align="center">
				<iframe width="1000px" height="700px" src="datav.php?VisualData\\1565b959dbb894e12ef10fe3322819d8\\B23K.csv"></iframe>
				</div>

		</div> 
		
		<div class="dhtmlgoodies_panel"> 
				<div align="center">
				<iframe width="1000px" height="700px" src="datav.php?VisualData\\1565b959dbb894e12ef10fe3322819d8\\B23K.csv"></iframe>
				</div>

		</div> 
		
		
		
		
	</div> 
	<!-- END OF PANE CONTENT --> 

<?

$test = "计算机";
$fields = "'$test','云计算','移动装置'";
?>

	<script type="text/javascript">

	//var fields = new Array("'计算机','云计算','移动装置'");
	//	var fields = new Array("<? echo "$strfileds";?>");
	//	var bools = new Array("<? echo "$strbools";?>");
	//	var panes = new Array("<? echo "$strpanes";?>");
	//	alert(fields[1]);alert(bools);alert(panes);
	//	initDhtmlgoodies_xpPane(Array(field),Array(bools),Array(panes));
		
	</script>
	<? 
	
	echo "<script type=\"text/javascript\">";
	echo "	var fields = new Array($fields);";
	echo "	var panes = new Array('pane1','pane2','pane3');";
	echo "	initDhtmlgoodies_xpPane(fields,panes);";
	echo "</script>";
	
	?>

</div> 

</body> 
</html>
