<?php
if ($_POST['chlodzenie'] < 0 || $_POST['chlodzenie'] > 50 || 
$_POST['grzanie'] < 0 || $_POST['grzanie'] > 50 || 
$_POST['suszenie'] > 90 || $_POST['nawilzanie'] > 90 || 
$_POST['nawilzanie'] < 20 || $_POST['suszenie'] < 20) echo("PRZEKROCZONO ZAKRES CZUJNIKÓW");
else if ($_POST['chlodzenie'] - $_POST['grzanie'] < 3) echo("TEMPERATURA STARTU CHŁODZENIA MUSI BYĆ O CO NAJMNIEJ 3 STOPNIE WYŻSZA OD TEMPERATURY STARTU GRZANIA");
else if ($_POST['suszenie'] - $_POST['nawilzanie'] < 3) echo("WARTOŚĆ STARTU SUSZENIA MUSI BYĆ O CO NAJMNIEJ 3 PUNKTY PROCENTOWA WYŻSZA OD WARTOŚCI STARTU NAWILŻANIA");
else
{
    $plikgrzania = fopen("progi/grzanie.txt", "w");
    fwrite($plikgrzania, $_POST['grzanie']);
    fclose($plikgrzania);
    $plikchlodzenia = fopen("progi/chlodzenie.txt", "w");
    fwrite($plikchlodzenia, $_POST['chlodzenie']);
    fclose($plikchlodzenia);
    $plikdobrejtemperatury = fopen("progi/dobratemperatura.txt", "w");
    fwrite($plikdobrejtemperatury, $_POST['dobratemperatura']);
    fclose($plikdobrejtemperatury);
    $pliksuszenia = fopen("progi/suszenie.txt", "w");
    fwrite($pliksuszenia, $_POST['suszenie']);
    fclose($pliksuszenia);
    $pliknawilzania = fopen("progi/nawilzanie.txt", "w");
    fwrite($pliknawilzania, $_POST['nawilzanie']);
    fclose($pliknawilzania);
    $plikdobrejwilgotnosci = fopen("progi/dobrawilgotnosc.txt", "w");
    fwrite($plikdobrejwilgotnosci, $_POST['dobrawilgotnosc']);
    fclose($plikdobrejwilgotnosci);
    echo("USTALONO NOWE PROGI");
}
?>