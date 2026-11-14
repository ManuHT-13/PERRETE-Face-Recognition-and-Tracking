@echo off
setlocal
rem Usage: export_to_engine.bat <path_no_extension> [dynamic]
rem Example:  export_to_engine.bat models\perrete_face_test\perrete_face dynamic
rem Disclaimer: Shapes for imgsz of 640

if "%~1"=="" (echo Usage: export_to_engine.bat <path_no_extension> [dynamic] & exit /b 1)

set BASE=%~1
set SHAPES=
if /i "%~2"=="dynamic" set SHAPES=--minShapes=images:1x3x320x320 --optShapes=images:1x3x640x640 --maxShapes=images:1x3x640x640

trtexec --onnx=%BASE%.onnx --saveEngine=%BASE%.engine --fp16 %SHAPES%