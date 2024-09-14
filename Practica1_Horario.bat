@echo off

Color 3F

REM menú de entrada para el usuario agregando las multiples opciones.

: menu
cls
echo =======================
echo  Gestor de Horarios
echo =======================
echo 1. Agregar Materia y Horario
echo 2. Eliminar Materia
echo 3. Mostrar Horario
echo 4. Eliminar Todo el Horario
echo 5. Guardar Horario en PDF
echo 6. Salir
echo =======================
set /p var="Elija una opcion: "

REM Condicionales para la seleccion de alguna opcion marcada en el menú y una vez seleccionada redireccionar a la etiqueta correspondiente

if "%var%"=="1" goto agregar
if "%var%"=="2" goto eliminar
if "%var%"=="3" goto mostrar
if "%var%"=="4" goto eliminar_todo
if "%var%"=="5" goto guardar_pdf
if "%var%"=="6" exit

goto menu

REM una vez ingresados los dato se almacenan en un archivo txt

:agregar
cls
set /p materia="Ingrese el nombre de la materia: "
set /p hora="Ingrese el horario (Ej: 3:00-4:00): "
echo %materia%             %hora% >> horario.txt
echo Materia y horario agregados!
pause
goto menu

:eliminar
cls

set /p delete="Ingrese el nombre de la materia que desea eliminar: "
findstr /v /c:"%delete%" horario.txt > temp.txt
move temp.txt horario.txt
echo Materia eliminada!
pause
goto menu

REM una vez impreso el mensaje en el encabezado de la tabla se agrega un for para mostrar los datos almacenados previamente


:mostrar
cls
echo ================ Horario =================
echo Materia        Horario
echo ==========================================
for /f "tokens=*" %%a in (horario.txt) do echo %%a
echo ==========================================
pause
goto menu


:eliminar_todo
cls
echo Está seguro de que desea eliminar todo el horario? (S/N)
set /p confirm="Ingrese su elección: "
if /i "%confirm%"=="S" (
    echo. > horario.txt
    echo Todo el horario ha sido eliminado!
) else (
    echo Operación cancelada.
)
pause
goto menu

:guardar_pdf
cls
echo Guardando en PDF...

REM Este paso depende de tener una herramienta de conversión

notepad.exe /p horario.txt
pause
goto menu
