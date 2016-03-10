<?php/*
    
    Copyright (C) <2016>  <Luciano Bigiotti && Riccardo Nocella>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
     ?>




<!doctype html>
<html>
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <?php
            include ("connect.php");
            include("create_db_table.php");
            include ( "csv/import2_csv.php");
            
            csv_import();
        ?>
        <title>Home Page</title>
        <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
        <link href="site_lib/dataTables.bootstrap.min.css" rel="stylesheet">
        
    <link href="site_lib/dataTables.bootstrap.css" rel="stylesheet">
    <link href="site_lib/dataTables.responsive.css" rel="stylesheet">

    <script src="site_lib/jquery-1.11.1.min.js"></script>
    <script src="site_lib/jquery.dataTables.js"></script>
    <script src="site_lib/dataTables.responsive.js"></script>
    <script src="site_lib/dataTables.bootstrap.js"></script>
    <script src="site_lib/jquery.dataTables.min.js"></script>
<style>body { font-size: 140% }

    table.dataTable th,
    table.dataTable td {
        white-space: nowrap;
    }</style>

    </head>



    <body background="img/bg.jpg">

        <div class="row">
            <div class="col-xs-12 col-md-9">
                <font face=”Geneva”>
                    <h3 align="center" style="color:orange">Udoo dati Birra</h3>
                    <br>
                    <?php
                        $today = date("j/n/Y");
                        $today_sel="%".$today."%";

                        $qp = "SELECT * FROM udoo_dati WHERE Data like '".$today_sel."' ";
                        $rp = mysql_query($qp);
                        $np = mysql_num_rows($rp);



                        if ($np < 1) {
                            echo '<h2 style="color:red">Nessun dato acquisito</h2>';
                        }
                        else {
                            echo '<div class="panel-body" align="center">';
                            echo '<div class="table-responsive" align="center">
                                <table id="myTable" class="table table-striped table-hover dt-responsive" cellspacing="0" width="100%">

                                  <thead>
                                  <tr>
                                <th class="danger">Temperature</th>
                                <th class="danger">Alcohol</th>
                                <th class="danger">Pressure</th>
                                <th class="danger">Time</th> </tr> </thead><tbody>';

                                for($i=0;$i<$np;$i++) {
                                    $rip = mysql_fetch_array($rp);

                                    echo '<tr>
                                          <td class="info">'.$rip['Temperature'].'</td>
                                          <td class="info">'.$rip['Alcohol'].'</td>
                                          <td class="info">'.$rip['Pressure'].'</td>
                                          <td class="info">'.$rip['Hour'].':'.$rip['Minute'].':'.$rip['Second'].'</td>
                                          </tr>
                                          ';

                                }



                            echo '</tbody></table>
                                          </div></div>';
                        }

                        /*  for($i=0;$i<$np;$i++) {
                        if ($rip['Temperature'] < 22  )  {
                            var_dump($rip['Temperature']);
                            $mex="problema termico, accensione cinta";
                            $dest="riccardo.nocella@yahoo.it";
                            $subject="udooo-system-monitor";
                            $headers = "From: udoo@example.com" . "\r\n";
                            if(mail($dest,$subject,$mex,$headers)){
                              echo "ok,mail inviata";

                            }else echo "impossibile inviare mail";


                        }}*/


                    ?>

                    <!--<script type="text/JavaScript">

                    function timedRefresh(timeoutPeriod) {
                    	setTimeout("location.reload(true);",timeoutPeriod);
                    }

                    window.onload = timedRefresh(5000);

                    //                      </script> -->

                </font>

            </div>
        </div>
        <script>
        $(document).ready(function() {
      $('#myTable').DataTable();
          } );
            </script>

    </body>
</html>
