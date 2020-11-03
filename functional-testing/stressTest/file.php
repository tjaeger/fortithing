<?php 

// for testing ONLY! No production with this crappy code!
// intended to be runned on your LAN for board testing purpose

	$file_acc = fopen("accelerometer.csv", "a") or die("Unable to open accelerometer file!");
	$file_temp = fopen("temperature.csv", "a") or die("Unable to open temperature file!");

	$data = htmlspecialchars($_GET["data"]);	// get datas from ESP32

	$sensor = strstr($data, ';', true);		// get returned sensor

	$values = substr(strstr($data, ';'),1);
	$values = str_replace(";",",",$values);		// change ; in , for the CSV
	$values = str_replace("_","",$values);		// trim '_' char

	if (strcmp($sensor,"acc")==0) {
		fwrite($file_acc,$values."\n");
	} else if (strcmp($sensor,"temp")==0)
		fwrite($file_temp ,$values."\n");

	print rand(0,2); 	// 0, 1 or 2 (warning: 2 doesn't exist on ESP32 board)
?>
