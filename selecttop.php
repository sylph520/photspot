<SCRIPT LANGUAGE="JavaScript">
document.onmousedown = function(e)
{
	fireEvent();
	var obj;
	if(event.srcElement!=null)
	{
		obj=event.srcElement;		
	}
	else
	{
		obj=e.target;
	}

	var srcobj = document.getElementById("country");	

	if(event.clientX<srcobj.offsetLeft || event.clientX>(srcobj.offsetLeft+srcobj.offsetWidth) || event.clientY<srcobj.offsetTop || event.clientY>srcobj.offsetTop+srcobj.offsetHeight)
	{
		document.getElementById("country").style.display = "none";
	}
    
	var srcobj2 = document.getElementById("myType");	

	if(event.clientX<srcobj2.offsetLeft || event.clientX>(srcobj2.offsetLeft+srcobj2.offsetWidth) || event.clientY<srcobj2.offsetTop || event.clientY>srcobj2.offsetTop+srcobj2.offsetHeight)
	{
		document.getElementById("myType").style.display = "none";
	}
}

function fireEvent()
{
	if(window.Event){
	 window.constructor.prototype.__defineGetter__("event", function(){
	  var o = arguments.callee.caller;
	  var e;
	  while(o != null){
	   e = o.arguments[0];
	   if(e && (e.constructor == Event || e.constructor == MouseEvent)) return e;
	   o = o.caller;
	  }
	  return null;
	 });
	}
}

</SCRIPT>
<?
session_start();
?>
<tr>
<td colspan="2" align="left">
<TABLE cellpadding="0" cellspacing="0" border=0>
 <TR>
	<TD width="35" NOWRAP align=right>����&nbsp;</TD>
	<TD width="50"><input id="selCountry" name="selCountry" size=10 style='background-color: #E5F1F9;height: 20px;
FONT-SIZE: 12px;color: #003399;' value=<?if ($guojia!='') echo $guojia; else echo "���й���";?>>
		<div nowrap id="country" style="height:150px;overflow:auto;border: 2px inset #FFFFFF;position:absolute; left:94px; top:69px;background-color: #E5F1F9; border: 1 solid silver;display: none;">
		  <SCRIPT LANGUAGE="JavaScript">
			_checkbox("city","���й���;AP-���޹�ҵ��Ȩ��֯;AR-����͢;AT-�µ���;AU-�Ĵ�����;BA-��˹���Ǻ�����ά��;BE-����ʱ;BG-��������;BR-����;CA-���ô�;CH-��ʿ;CN-�й�;CS-�ݿ�˹�工��;CU-�Ű�;CY-����·˹;CZ-�ݿ�;DD-ǰ�¹�;DE-�¹�;DK-����;EA-ŷ��ר����֯;EE-��ɳ����;EG-����;EP-ŷ��ר����;ES-������;FI-����;FR-����;GB-Ӣ��;GR-ϣ��;HR-���޵���;HU-������;IE-������;IL-��ɫ��;IN-ӡ��;IT-�����;JP-�ձ�;KE-������;KR-����;LT-������;LU-¬ɭ��;LV-����ά��;MC-Ħ�ɸ�;MD-Ħ������;MN-�ɹ�;MT-�����;MW-����ά;MX-ī����;MY-��������;NC-�¿��������;NL-����;NO-Ų��;NZ-������;OA-����֪ʶ��Ȩ��֯;PH-���ɱ�;PL-����;PT-������;RO-��������;RU-����˹����;SE-���;SG-�¼���;SI-˹��������;SK-˹�工��;SU-����;TJ-������˹̹;TR-������;TT-�������Ͷ�͸�;US-����;VN-Խ��;WO-����֪ʶ��Ȩ��֯;YU-��˹����;ZA-�Ϸ�;ZM-�ޱ���;ZW-��Ͳ�Τ","","selCountry");
		  </SCRIPT>
		</div></TD>
    <TD width="16" NOWRAP align=center><div style="position:relative; left:-18px; top:1px; "><img src="../images/downlist.gif"  border="0" id="imgCountry"   onclick="if(country.style.display==''){country.style.display='none';}else{country.style.display='';} myType.style.display='none'">
	</div></td>

    <TD width="30" NOWRAP align=right>ʡ��&nbsp;</TD>
    <TD width="50"><input id="selCountry2" name="selCountry2" size=10 style='background-color: #E5F1F9;height: 20px;
	FONT-SIZE: 12px;color: #003399;' value=<?if ($shengshi!='') echo $shengshi; else echo "����ʡ��";?>>
        <div nowrap id="myType" style="height:120px;overflow:auto;border: 2px inset #FFFFFF;position:absolute; left:260; top:69;background-color: #E5F1F9; border: 1 solid silver;display: none;">
           <script language="JavaScript">
_checkbox("city2","����ʡ��;CN11-����;CN15-����;CN31-�Ϻ�;CN35-����;CN42-����;CN51-�Ĵ�;CN61-����;CN65-�½�;CN83-�人;CN91-����;CN14-ɽ��;CN23-������;CN34-����;CN41-����;CN45-����;CN54-����;CN64-����;CN81-����;CN89-����;CN13-�ӱ�;CN22-����;CN33-�㽭;CN37-ɽ��;CN44-�㶫;CN53-����;CN63-�ຣ;CN71-̨��;CN87-����;CN95-�ൺ;CN12-���;CN21-����;CN32-����;CN36-����;CN43-����;CN52-����;CN62-����;CN66-����;CN85-����;CN93-������;HK-���;TW-̨��","","selCountry2");
           </script>
       </div></TD>
    <TD width="16" NOWRAP align=center><div style="position:relative; left:-18px; top:1px; "><img src="../images/downlist.gif"  border="0" id="imgCountry"   onclick=" if(myType.style.display==''){myType.style.display='none';}else{myType.style.display='';}; country.style.display='none'"> </div></td>  

	<TD width="75" NOWRAP align=center><select id=selDate name='selDate'>
	  <option <?if ($gonggaori=='') echo 'selected';?>  value='gpd'>������</option>
	  <option value='ad' <?if ($gonggaori==1) echo 'selected';?>>������</option>
	</select></TD>
                            
	<TD width="58" NOWRAP><INPUT type="radio" id=raDate name=raDate onClick="if(raDate.checked){raDate1.checked=false;}" <?if ($nianfen!='') echo 'checked';?>>
	���</TD>
    <TD width="63" NOWRAP>
			<SELECT id=selYear name=selYear>        
              <OPTION value=1966 <?if ($nian=='1966') echo 'selected';?>>1966</OPTION>              
              <OPTION value=1967 <?if ($nian=='1967') echo 'selected';?>>1967</OPTION>             
              <OPTION value=1968 <?if ($nian=='1968') echo 'selected';?>>1968</OPTION>              
              <OPTION value=1969 <?if ($nian=='1969') echo 'selected';?>>1969</OPTION>              
              <OPTION value=1970 <?if ($nian=='1970') echo 'selected';?>>1970</OPTION>              
              <OPTION value=1971 <?if ($nian=='1971') echo 'selected';?>>1971</OPTION>             
              <OPTION value=1972 <?if ($nian=='1972') echo 'selected';?>>1972</OPTION>              
              <OPTION value=1973 <?if ($nian=='1973') echo 'selected';?>>1973</OPTION>              
              <OPTION value=1974 <?if ($nian=='1974') echo 'selected';?>>1974</OPTION>              
              <OPTION value=1975 <?if ($nian=='1975') echo 'selected';?>>1975</OPTION>             
              <OPTION value=1976 <?if ($nian=='1976') echo 'selected';?>>1976</OPTION>             
              <OPTION value=1977 <?if ($nian=='1977') echo 'selected';?>>1977</OPTION>              
              <OPTION value=1978 <?if ($nian=='1978') echo 'selected';?>>1978</OPTION>              
              <OPTION value=1979 <?if ($nian=='1979') echo 'selected';?>>1979</OPTION>              
              <OPTION value=1980 <?if ($nian=='1980') echo 'selected';?>>1980</OPTION>              
              <OPTION value=1981 <?if ($nian=='1981') echo 'selected';?>>1981</OPTION>              
              <OPTION value=1982 <?if ($nian=='1982') echo 'selected';?>>1982</OPTION>              
              <OPTION value=1983 <?if ($nian=='1983') echo 'selected';?>>1983</OPTION>              
              <OPTION value=1984 <?if ($nian=='1984') echo 'selected';?>>1984</OPTION>              
              <OPTION value=1985 <?if ($nian=='1985') echo 'selected';?>>1985</OPTION>              
              <OPTION value=1986 <?if ($nian=='1986') echo 'selected';?>>1986</OPTION>              
              <OPTION value=1987 <?if ($nian=='1987') echo 'selected';?>>1987</OPTION>              
              <OPTION value=1988 <?if ($nian=='1988') echo 'selected';?>>1988</OPTION>              
              <OPTION value=1989 <?if ($nian=='1989') echo 'selected';?>>1989</OPTION>              
              <OPTION value=1990 <?if ($nian=='1990') echo 'selected';?>>1990</OPTION>              
              <OPTION value=1991 <?if ($nian=='1991') echo 'selected';?>>1991</OPTION>
              <OPTION value=1992 <?if ($nian=='1992') echo 'selected';?>>1992</OPTION>
              <OPTION value=1993 <?if ($nian=='1993') echo 'selected';?>>1993</OPTION>
              <OPTION value=1994 <?if ($nian=='1994') echo 'selected';?>>1994</OPTION>
              <OPTION value=1995 <?if ($nian=='1995') echo 'selected';?>>1995</OPTION>
              <OPTION value=1996 <?if ($nian=='1996') echo 'selected';?>>1996</OPTION>
              <OPTION value=1997 <?if ($nian=='1997') echo 'selected';?>>1997</OPTION>              
              <OPTION value=1998 <?if ($nian=='1998') echo 'selected';?>>1998</OPTION>              
              <OPTION value=1999 <?if ($nian=='1999') echo 'selected';?>>1999</OPTION>
              <OPTION value=2000 <?if ($nian=='2000') echo 'selected';?>>2000</OPTION>
              <OPTION value=2001 <?if ($nian=='2001') echo 'selected';?>>2001</OPTION>
              <OPTION value=2002 <?if ($nian=='2002') echo 'selected';?>>2002</OPTION>              
              <OPTION value=2003 <?if ($nian=='2003') echo 'selected';?>>2003</OPTION>              
              <OPTION value=2004 <?if ($nian=='2004') echo 'selected';?>>2004</OPTION>              
              <OPTION value=2005 <?if ($nian=='2005') echo 'selected';?>>2005</OPTION>
              <OPTION value=2006 <?if ($nian=='2006') echo 'selected';?>>2006</OPTION>
			<OPTION value=2007 <?if ($nian=='2007') echo 'selected';?>>2007</OPTION>
			<OPTION value=2008 <?if ($nian=='2008') echo 'selected';?>>2008</OPTION>
			<OPTION value=2009 <?if ($nian=='2009') echo 'selected';?>>2009</OPTION>
			<OPTION value=2009 <?if ($nian=='2010') echo 'selected';?>>2010</OPTION>
			<OPTION value=2009 <?if ($nian=='2011') echo 'selected';?>>2011</OPTION>
			<OPTION value=2009 <?if ($nian=='2012'||$nian=='') echo 'selected';?>>2012</OPTION>

            </SELECT></TD>
	<TD width="62" NOWRAP><INPUT type="radio" id=raDate1 name=raDate1 onClick="if(raDate1.checked){raDate.checked=false;}" <?if ($shijian!='') echo 'checked';?>>
	ʱ��&nbsp;</TD>
	<TD width="110" NOWRAP><input name=txBegDate class="input1" id=txBegDate  value=<?if ($Datime1!='') echo $Datime1; else echo "1985-01-01";?>>
	  <A onClick="event.cancelBubble=true;" href="javascript:showCalendar('dimg2',true,'txBegDate')"><IMG src="../images/clock.gif" alt="" border="0" align="absMiddle" id="dimg2"></A>&nbsp;��&nbsp;</TD>
	<TD width="95" NOWRAP><INPUT name=txEndDate class="input1" id=txEndDate  value="<?if ($Datime2!='') echo $Datime2; else echo date('Y-m-d',time());?>">
	  <A onClick="event.cancelBubble=true;" href="javascript:showCalendar('dimg1',true,'txEndDate')"><IMG src="../images/clock.gif" alt="" border="0" align="absMiddle" id="dimg1"></A></TD> 
	  
	  <td width="100"> <INPUT type="checkbox" id=fuzzyQuery name=fuzzyQuery <?if ($fuzzyQuery!='') echo 'checked';?>>ģ������</TD>
</tr>
</table></td></tr>