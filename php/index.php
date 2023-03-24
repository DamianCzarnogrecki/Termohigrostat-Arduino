<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>TERMOHIGROSTAT</title>
  </head>
  <body style="background-color:aquamarine;">
    <form method="post" action="progi.php">

    <p>ZACZNIJ GRZAĆ OD (°C):</p>
    <input type="number" name="grzanie"/>
    <br/>

    <p>ZACZNIJ CHŁODZIĆ OD (°C):</p>
    <input type="number" name="chlodzenie"/>
    <br/>

    <p>OPTYMALNA TEMPERATURA (°C):</p>
    <input type="number" name="dobratemperatura"/>
    <br/>

    <p>ZACZNIJ SUSZYĆ OD (%):</p>
    <input type="number" name="suszenie"/>
    <br/>

    <p>ZACZNIJ NAWILŻAĆ OD (%):</p>
    <input type="number" name="nawilzanie"/>
    <br/>

    <p>OPTYMALNA WILGOTNOŚĆ (°C):</p>
    <input type="number" name="dobrawilgotnosc"/>
    <br/>

    <br/>
    <button type="submit">ZATWIERDŹ</button>
    </form>
  </body>
</html>