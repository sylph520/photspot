<div id=loading style.display="">
<?php
   include('../function/loading.php');
?>
</div>
<?php
    include("../function/dbconfig.php");
   
    //author: WanPeng
    //date: 2012-03-24
    //function: 从$real_table中去除在__system表中已经不存在的数据表，要放在dbconfig.php之后（涉及数据库操作）
    include("../function/seltablecheck.php");
?>

<?
session_start(); 
    $patent_en=array("申请日"			=>"ad",
					 "专利名称"			=>"ti",
					 "文 摘"			=>"ab",
					 "公开日"		    =>"gpd",
					 "专利权人"	        =>"pa",
					 "发明人"			=>"inn",
					 "IPC主分类号"		=>"ic1",);

if (!$_SESSION['tempan'])
session_register("tempan");

date_default_timezone_set('PRC');//设置默认时区为中国时区


//去除检索条件中申请号、公开号、优先权项、主分类号、副分类号、外观分类号前的所有空格及“*”字符；
function RemoveCharacter($query)
{
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"gpn:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 4))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 4))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 4;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"gpn:cn",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 6))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 6))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 6;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"an:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 3))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 3))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 3;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"an:cn",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 5))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 5))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 5;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"pr:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 3))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 3))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 3;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"ic1:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 4))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 4))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 4;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"ic2:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 4))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 4))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 4;
		}
	}
	$start = 0;
	 while($start!==false)
	 {
		 $start=strpos($query,"wg:",$start);
		 if($start!==false)
		{
			 do
			 {
				 $flag = false;
				 $pos1 = strpos($query," ",$start);
				 $pos2 = strpos($query,"*",$start);
				 if($pos1 !== false && ($pos1 - $start == 3))
				 {
					 $query = substr($query,0,$pos1).substr($query,$pos1+1,strlen($query)-$pos1);
					 $flag = true;
				 }
				elseif($pos2 !== false && ($pos2 - $start == 3))
				{
					 $query = substr($query,0,$pos2).substr($query,$pos2+1,strlen($query)-$pos2);
					 $flag = true;
				 }	
			}while($flag == true);								
								
			$start = $start + 3;
		}
	}
	return $query;
}
?>


<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<LINK href="../css/style.css" type="text/css" rel=stylesheet>
<LINK href="css/pane.css" type="text/css" rel=stylesheet>
<link rel="stylesheet" type="text/css" href="wbox/wbox.css" />
<title>热点检索</title>
<script type="text/javascript" src="js/jquery1.4.2.js"></script> 
<script type="text/javascript" src="js/wbox.js"></script> 
<style type="text/css">
	body{
		margin:0 auto;
		background-color:#ffffff;
	}
	
	#popupMsg{
		position:absolute; z-index:100; display:none; background-color:#eeeeee;
		}

	#dialog
	{   
		position: absolute;
		visibility: hidden;
		overflow: hidden;
		background-color:#F6F6F6;
		border:10px solid #666;
		padding:5px;
	}
</style>
<script language="javascript" src="../js/search.js"></script>


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

<script type="text/javascript"> 
	
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
	
	function Get_Cookie(name) 
	{ 
	   var start = document.cookie.indexOf(name+"="); 
	   var len = start+name.length+1; 
	   if ((!start) && (name != document.cookie.substring(0,name.length))) return null; 
	   if (start == -1) return null; 
	   var end = document.cookie.indexOf(";",len); 
	   if (end == -1) end = document.cookie.length; 
	   return unescape(document.cookie.substring(len,end)); 
	}
	
	// This function has been slightly modified
	function Set_Cookie(name,value,expires,path,domain,secure) 
	{ 
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
		if(img.src.toLowerCase().indexOf('up')>=0)
		{
			currentlyExpandedPane = false;
			img.src = img.src.replace('up','down');
			if(xpPanel_slideActive)
			{
				obj.style.display='block';
				xpPanel_currentDirection[obj.id] = (xpPanel_slideSpeed*-1);
				slidePane((xpPanel_slideSpeed*-1), obj.id);
			}
			else
			{
				obj.style.display='none';
			}
			if(cookieNames[numericId])Set_Cookie(cookieNames[numericId],'0',100000);
		}
		else
		{
			if(this)
			{
				if(currentlyExpandedPane && xpPanel_onlyOneExpandedPane)showHidePaneContent(false,currentlyExpandedPane);
				currentlyExpandedPane = this;	
			}else
			{
				currentlyExpandedPane = false;
			}
			img.src = img.src.replace('down','up');
			if(xpPanel_slideActive)
			{
				if(document.all)
				{
					obj.style.display='block';
					//obj.style.height = '1px';
				}
				xpPanel_currentDirection[obj.id] = xpPanel_slideSpeed;
				slidePane(xpPanel_slideSpeed,obj.id);
			}
			else
			{
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
		if(slideValue!=xpPanel_currentDirection[id])
		{
			return false;
		}
		var activePane = document.getElementById(id);
		if(activePane==savedActivePane)
		{
			var subDiv = savedActiveSub;
		}else
		{
			var subDiv = activePane.getElementsByTagName('DIV')[0];
		}
		savedActivePane = activePane;
		savedActiveSub = subDiv;
		
		var height = activePane.offsetHeight;
		var innerHeight = subDiv.offsetHeight;
		height+=slideValue;
		if(height<0)height=0;
		if(height>innerHeight)height = innerHeight;
		
		if(document.all)
		{
			activePane.style.filter = 'alpha(opacity=' + Math.round((height / subDiv.offsetHeight)*100) + ')';
		}
		else
		{
			var opacity = (height / subDiv.offsetHeight);
			if(opacity==0)opacity=0.01;
			if(opacity==1)opacity = 0.99;
			activePane.style.opacity = opacity;
		}			
		
					
		if(slideValue<0)
		{			
			activePane.style.height = height + 'px';
			subDiv.style.top = height - subDiv.offsetHeight + 'px';
			if(height>0)
			{
				setTimeout('slidePane(' + slideValue + ',"' + id + '")',10);
			}
			else
			{
				if(document.all)activePane.style.display='none';
			}
		}
		else
		{			
			subDiv.style.top = height - subDiv.offsetHeight + 'px';
			activePane.style.height = height + 'px';
			if(height<innerHeight)
			{
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


<BODY leftMargin=0 topMargin=0 style="BACKGROUND-REPEAT: repeat-x" bgColor=#ffffff background="../images/back_new2.gif" onLoad="loading.style.display='none'" >



<div>
<TABLE style="BACKGROUND-REPEAT: repeat-x" cellSpacing=0 cellPadding=0 width=100% height=100%
align=center bgColor=#ffffff background="../images/back_new2.gif" border=0>

<tr><td height=10>&nbsp;</td></tr>
  <TR>
    <TD align=center width=100%>
	  <TABLE cellSpacing=0 cellPadding=0 border=0> 
		<TR>
		  <TD align="center" valign="top" width=100%>

			<? 
			
				if ((count($real_table)==0))
				{
					echo "请至少选择一个待查询的数据库！<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";exit;
				}
				$ta = array();  	// 判断是普通查询还是历史查询	
				$ta = $real_table;	// $real_table为右边导航栏前面打勾的表;
						
				$dbnum=count($ta);
	
				//热点查询

				$q_absti = "@absti:$absti";

				if ($yearbegin=='' && $yearend=='' && $absti=='' && 
						$techclassification=='' && $patentee=='')
				{
					echo "请填写查询条件！<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";
				    pg_close($conn);
					exit();
				}
						
				$patentee = trim($patentee);
				if ($patentee!='')
				{	
					$showquery = " and "."(发明人:".$patentee." or 专利权人:".$patentee.")".$showquery;
					$txOriginator2 = "(pa:\"".$patentee."\" or inn:\"".$patentee."\")";
					$querycondition = " and ".$txOriginator2.$querycondition;
				}
						
				$absti = trim($absti);
				if ($absti!='')
				{
					$showquery=" and "."(名称:"."(".$absti.")"." or 文摘:"."(".$absti.")".")".$showquery;
					$txSubject2="(ti:(".$absti.") or ab:(".$absti."))";
					$querycondition=" and ".$txSubject2.$querycondition;
				}
						
				$formercondition = substr($querycondition, 5); //去掉最前面的and
						
				$sqltable='';
				for ($i=0; $i<$dbnum; $i++)
				{
					$sqltable.=$ta[$i].",";
				}
				$sqltable=substr($sqltable, 0, -1);
				$query = "(".$formercondition.")";				
				$query = RemoveCharacter($query);
		
				//保存历史表达式
				if(!empty($user_id))
				{
					$sql_num = $dbnum;

					if ($sql_num == 1)
					{
						$check_index = pg_exec($conn,"select indexed from __system where tablename = '".$sqltable."'");
						$rowrow = pg_fetch_row($check_index,0);
								
						if ($rowrow[0] == 'f')
						{
							echo "该表未建立索引，暂时不能查询!<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";
							pg_close($conn);
							exit;
						}
					}
					else
					{
						$sqltable = '';
						$rcd = array();	//新建数组保存没有索引的表名
						for($ci=0; $ci < $sql_num; $ci++)
						{
							$check_index = pg_exec($conn,"select indexed from __system where tablename = '".$ta[$ci]."'");
							$rowrow = pg_fetch_row($check_index,0);
			
							if ($rowrow[0] == 'f')
							{  
								$dis_tem = pg_exec($conn,"select display from __system where tablename = '".$ta[$ci]."'");
								$dis_row = pg_fetch_row($dis_tem,0);
								array_push($rcd,$dis_row[0]);		//把没有索引的表名放到$rcd中
							}
							else
							{
								$sqltable.=$ta[$ci].",";			//把有索引的表名重新存储进去
							}										
						}

						//把数组$rcd中内容放到变量$aert中。
						for ($d=0; $d< count($rcd); $d++)
						{
							$aert .= $rcd[$d];
							$aert .= ',';
						}
						$aert = substr($aert,0,-1);	//去掉最后的","。

						if (count($rcd) > 0)
						{
							echo "<script>alert('$aert 表没有建立索引！') </script>";		//打印出提示
						}
						$sqltable=substr($sqltable,0,-1);		
					}
							
				/*	$res = pg_exec($conn,"select search_ii_num('$sqltable','$query')");//$sqltable为选择的进行查询的数据库；$query为查询表达式
						echo "select search_ii_num('$sqltable','$query')";exit;
					if (!$res) 
					{	
						echo "您输入的语法存在错误，请仔细检查！<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";
						pg_close($conn);
						exit;
					}
							
					$row = pg_fetch_row($res,0);
					$num = $row[0];          //$num为检索满足条件的专利数目 石徳钏
*/
							
					/* 
					 * add by Wan Peng 
					 * date: 2013-05-17
					 * 判断满足条件的专利数目
					 * 如果条数为0或者条数大于50000都需要重新检索
					 */
					 $num = 100;
					if ($num<=0)
					{
						echo "满足条件的专利数目为0，导致本次分析无法进行，请检查您的输入条件！<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";
						pg_close($conn);
						exit;
					}
					else if ($num>50000)
					{
						echo "满足条件的专利数目查过50000条，请精确您的查询条件！<br><br><input type='button' name='back' value='返 回' onclick='history.go(-1);return false;' style='height:20px;width=62;background-color:#ffffff;border:1 solid #696969;font:12px;color=3c3c3c' onMouseOver = 'this.style.backgroundColor =\"cdd0f6\"' onMouseOut = 'this.style.backgroundColor=\"ffffff\"'>";
						pg_close($conn);
						exit;
					}
				}//保存历史表达式
				
				
								
	
               //进行真正的查询，并显示-------------------------------------------------
			
                $depen=$_POST['inpa'];		

				if($searchtype!=10)
				{
					$savedquery=$savedquery1;
				}							   
				else
				{
					$savedquery=$savedquery2;
				}

                $selectfield="an,ti,pa";

				$query="select * from  search_ii_oid('$sqltable','$savedquery','$selectfield','',true,0,0);";
				
		
				/* 构造检索表达式----------------------------------------------------------------------------------
				*  
				*  起始年份：yearbegin
				*  结束年份：yearend
				*  名称摘要：absti
				*  专利技术分类：techclassification
				*  专利权人：patentee
				*  粒度值：  大---degreeBig
				*  			 中---degreeMidlle
				*  			 小---degreeSmall
				*/
				$q_date = "@appyear:{$yearbegin}to{$yearend}";
				$q_sqltable = "@sqltable:$sqltable";
				$q_absti = "@absti:$absti";
				$q_ipc = "@ipc:$techclassification";
				$q_pa = "@pa:$patentee";
				// 粒度
				if ($degreeBig=='on')
				{
					$q_degree = "@degree:大";
				}
				else if ($degreeMidlle=='on')
				{
					$q_degree = "@degree:中";
				}
				else if ($degreeSmall=='on')
				{
					$q_degree = "@degree:小";
				}
				else
				{
					$q_degree = "@degree:大";
				}
				
				
				// 检索表达式$query_argv-----------------------------------
				// @sqltable: 选择的数据库表
				// @appyear: 申请年份的范围
				// @absti: 专利标题或摘要
				// @pa: 专利权人
				// @degree: 粒度值
				// 分隔符：___sep___
				// 例如："@sqltable:cn_2k,cn_2013052___sep___@absti:装置___sep___@ipc:B___sep___@pa:公司___sep___@degree:大"
				// -------------------------------------------------------------------------------------------------
				$query_argv = $q_sqltable."___sep___".$q_date."___sep___".$q_absti."___sep___".$q_ipc."___sep___".$q_pa."___sep___".$q_degree;	
							
				/* 通过后台调用.exe程序生成热点信息--------------------*/ 
				
				// 调用C++对满足条件的专利进行分词、聚类、热点发现、趋势分析，并将结果写入文件
				//	system("E:\\毕业设计\\PatentHotspots\\PatentHotspots\\PatentHotspots\\PatentHotspots.exe");
				//$last_line = exec("C:\\Users\\WP\\Desktop\\PatentHotspots-C++-2013-05-23\\PatentHotspots\\PatentHotspots\\PatentHotspots\\PatentHotspots.exe $query_argv");
				$cmd = "PatentHotspots.exe ".$query_argv; 
				system($cmd);     //cmd为数据处理程序和参数，目前由于数据库被更改导致出现数据库读取出现BUG，后期需要修改     
				
				// 根据检索表达式的MD5值，查找后台生成的目录
				// case 1：如果该目录不存在，则说明后台执行失败
				// case 2：如果该目录存在，但是是空的，说明检索结果为空，或检索结果中没有热点
				// case 3：如果该目录存在且里面存在.csv格式的数据，则将其读取进来
				
				$folder_name = md5($query_argv);
				//$folder_name = "5c47b8f6ec23fcf24644a2e3ef12ac6f";
				//echo $folder_name;
				//exit();
				$path_name = "VisualData\\".$folder_name."\\";		// 要读取的目录
				if (file_exists($path_name))
				{
					// dir exist
					/*
					  Version: 22 May 2013
					  Author:  Wan Peng
					  purpose: 读取某个目录下的文件
					 */

					//打开目录
					$fp=opendir($path_name);

					//阅读目录
					while (false != $file=readdir($fp))
					{
						//列出所有文件并去掉'.'和'..'
						if($file!='.' &&$file!='..')
						{
							//$file="$folder/$file";
							$file = "$path_name$file";

							//赋值给数组
							$arr_file[] = $file;
						}
					}
					
					//输出结果
					if (is_array($arr_file))
					{
						if (count($arr_file) > 0)
						{
							echo "<div id=\"pageContent\">";
							echo "<div id=\"dhtmlgoodies_xpPane\">";
							
							
							// 如果该目录下有数据，说明本次得到了热点技术
							// 获取目录下所有的数据文件，解析其中的信息
							// 用抽屉效果将其显示出来
							
							$strfileds = "";
							$strpanes = "";
							$npos = 1;
							while(list($key,$value)=each($arr_file))
							{
								// $key为在数组中的序号，$value为实际的值（数据路径）
								
								// 将数据文件路径的文件名称提取出来，存放到fnameofvalue中
								$fnameofvalue = "";
								$pos = strrpos($value, '\\');
								if ($pos===false)// 没有找到
								{
									return false;
								} 
								else
								{
									$fnameofvalue  = substr($value, $pos+1);
								}
								$fnameofvalue = str_replace('.csv', '', $fnameofvalue);
								
								
								// 将技术名称进行拼接，拼接后放到$strfileds中
								if ($strpanes == "")
								{
									$strfileds.= "'$fnameofvalue'";
									$strpanes.= "'pane$npos'";
								}
								else
								{
									$strfileds.= ",'$fnameofvalue'";
									$strpanes.= ",'pane$npos'";
								}
								echo "<div class=\"dhtmlgoodies_panel\">";
									echo "<div align=\"center\"><iframe width=\"1000px\" height=\"700px\" src=\"datav.php?datavpath=$value\"></iframe></div>";
								echo "</div>";
							//	echo "$key=>$value<br>";	
								++ $npos;
							}
							
							// 为每个子pane设置标题
							echo "</div>";
								echo "<script type=\"text/javascript\">";
								echo "	var fields = new Array($strfileds);";
								echo "	var panes = new Array($strpanes);";
								echo "	initDhtmlgoodies_xpPane(fields,panes);";
								echo "</script>";
							echo "</div>";
						}
						else
						{
							// 如果目录下没有数据文件，说明本次分析得到的热点技术个数为0
							echo  "本次检索没有热点技术，请重新检索！";
							exit();
						}
						
					}
					else
					{
						echo "本次检索结果为空，请重新检索!"; 
						exit();
					}

					//关闭目录
					closedir($fp);
				}
				else
				{
					// dir not exist
					echo "目录创建失败，请重新检索!"; 
					exit();
				}
			 
?>
</div>
</body>
</html>