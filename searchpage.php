<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<META http-equiv=pragma content=no-cache>
<LINK href="../css/style.css" type=text/css rel=stylesheet>
<link href="../css/downlist.css" rel="stylesheet" type="text/css">
<script type="text/javascript" language="javascript" src="../js/calendar.js"></script>
<script type="text/javascript" language="javascript" src="../js/downlist.js"></script>
<script language="javascript" src="../js/historydel.js"></script>
<script language="javascript" src="../js/opacity.js"></script>
<title>简单查询</title>
  
<style>
    body{
    	background-repeat:repeat-x;
    	background-image: url(..../images/back_new2.gif);
    }
    #maintable{
		background-repeat:repeat-x;
    	background-image: url(..../images/back_new2.gif);
    	width:100%;
    	height:99%;
    	background-color:#ffffff;
    	background-image: url(../images/back_new2.gif);
    	border:0px;
    }
</style>
</head>
<body>
<? 
session_start();
?>
<table align=center id="maintable" cellSpacing=0 cellPadding=0 >
	<tr><td height=30></td>	</tr>
	<tr>
		<td align=center valign=top >	
			<table cellpadding=1 cellspacing=1 bgcolor="#1888d4" width=80%>
				<tr>
					<td background="../images/linebg01.jpg" style="display:-webkit-box;-webkit-box-align:center" width=100%>
						<img src="../images/arrow02.gif" width="17" height="17" hspace="8">
						<span class="white12bold">热 点 检 索</span>
					</td> 
				</tr>
				<tr>
					<td height="100%" bgcolor="#f7f7f7">
						<form name="Form2" action="search_result.php?searchtype=0&searched=false&from=1&pfrom=1&image=yes" method="post" enctype="multipart/form-data" onSubmit="this.image.disabled=true;"  enablecab="yes">
						<table width="100%" border="0" cellpadding="0" cellspacing="0"  style="table-layout: fixed">
							<tr height="28px">
								<td width="45%" height="18" align=right NOWRAP>申请日(App Date)&nbsp;</td>
								<td NOWRAP align=left>
									<input  class="input11" type="text"  name="yearbegin" id="yearbegin" style="text-align:center;width:73px; height:23px;"  placeholder="1985" size="6" maxlength="4" onkeyup="value=value.replace(/[^\d]/g,'') "onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^\d]/g,''))">
									&nbsp;&nbsp; 至 &nbsp;&nbsp;
									<input class="input11" type="text" name="yearend" id="yearend" style="text-align:center; width:73px; height:23px;" placeholder="2017"  size="6" maxlength="4" onkeyup="value=value.replace(/[^\d]/g,'')" onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^\d]/g,''))">
								</td>
							</tr>
							<tr height="28px">
								<td  height="22" align=right NOWRAP>名 称/文 摘(Ti/Ab)&nbsp;</td>
								<td  NOWRAP>	<input  class="input10" name="absti" id="absti"  style="width:208" size="38" value=></td>
							</tr>
							<tr height="28px">
								<td  height="22" align=right NOWRAP>专利技术分类(Ipc)&nbsp;</td>
								<td colspan="2" NOWRAP>										
									<input class="input10" size=38 name=techclassification id="techclassification" style="width:208" onkeyup="value=value.replace(/[\W]/g,'') "onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^\d]/g,''))" onkeydown="if(event.keyCode==13)event.keyCode=9">
								</td>
							</tr>
							<tr height="28px">
								<td height="22" align=right NOWRAP>发明人/专利权人(Inn/Pa)&nbsp;</td>
								<td NOWRAP>	<input  class="input10" name="patentee" id="patentee" style="width:208" size=38 value=></td>
							</tr>
							<tr height="28px">
							     <td height="22" align=right NOWRAP><!--粒  度(Degree)&nbsp--></td>
								<!--TD>
									<input type="radio" id=degreeBig checked="checked" value="大" name="degreeBig"> 大 
									<input type="radio" id=degreeMidlle value="中" name="degreeMidlle"> 中 
									<input type="radio" id=degreeSmall  value="小" name="degreeSmall"> 小 
								</TD-->
								<td width="266" NOWRAP>             
									<a href="#"><img src="../images/search.gif" onClick="javascript:Form2.submit();return recommendBloger_forPopm('5210')" width="80" height="25" hspace="4" border="0">
									</a>
									<a href="#"><img src="../images/clear.gif" border=0 onClick="document.Form2.reset();" width="80" height="25" hspace="10"></a>
								</td>
							</tr>
						</table>
						</form>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
</body>
</html>








 