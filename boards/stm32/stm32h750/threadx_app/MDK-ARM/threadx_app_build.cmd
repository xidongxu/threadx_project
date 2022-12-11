@echo off
copy %~dp0threadx_app\threadx_app.map %~dp0build\threadx_app.map
copy %~dp0threadx_app\threadx_app.hex %~dp0build\threadx_app.hex
copy %~dp0threadx_app\threadx_app.axf %~dp0build\threadx_app.axf