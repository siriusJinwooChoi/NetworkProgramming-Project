<?php     
    $connect = mysql_connect("127.0.0.1", "root", "apmsetup")
                        or die("Disable connect to DB");
    mysql_select_db("test");

    
    $value = $_REQUEST[val];
       
    
    $qry = "insert into info values ('$value');";
    //$result = mysqli_query($connect, $qry);
        $result = mysql_query($qry);
     
    mysql_close($connect);

        echo ("PHP: hello world");
?>