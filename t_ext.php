<?php
//  dl('test_ext.so');

	$str = "abcdefg";
for($i=0;$i<10000000;$i++){
 ext_substr($str,1);
}

?>
