<?php
	session_start(); 
    include("../function/dbconfig.php");
   
    //author: WanPeng
    //date: 2012-03-24
    //function: 从$real_table中去除在__system表中已经不存在的数据表，要放在dbconfig.php之后（涉及数据库操作）
    include("../function/seltablecheck.php");
    date_default_timezone_set('PRC');//设置默认时区为中国时区
    header("Content-Type:text/html;charset=UTF-8"); 

	$ta = array();  	// 判断是普通查询还是历史查询	
	$ta = $real_table;	// $real_table为右边导航栏前面打勾的表;
	$dbnum=count($ta);
	$sqltable='';
	for ($i=0; $i<$dbnum; $i++)
	{
		$sqltable.=$ta[$i].",";
	}
	$sqltable=substr($sqltable, 0, -1);
	$query = "(".$formercondition.")";				
	$query = RemoveCharacter($query);

	$labmainid=$_POST['labmainid'];
	$conn=pg_connect($connect);
	$query="select * from  labmain where labmainid='$labmainid'";
	if(@$result=pg_query($conn,$query)){
		$listarray=pg_fetch_array($result,0);
		$list=array("labmainname"=>$listarray['labmainname'],"labmaintype"=>$listarray['labmaintype'],
		"labmainid"=>$listarray['labmainid'],"labmainauthorcom"=>$listarray['labmainauthorcom'],
		"labmainauthortime"=>$listarray['labmainauthortime'],"labmainauthorfile"=>$listarray['labmainauthorfile'],
		"labmainincludecom"=>$listarray['labmainincludecom'],"labmaincomrank"=>$listarray['labmaincomrank'],
		"labmainincludesubject"=>$listarray['labmainincludesubject'],
		"labmainsubjectrank"=>$listarray['labmainsubjectrank']); 
		echo json_encode($list); 
	}

?>

