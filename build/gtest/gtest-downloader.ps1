# Download Google Test
$webclient = New-Object System.Net.WebClient
$url = "https://github.com/google/googletest/archive/release-1.7.0.zip"
$dlfilename = $env:TEMP+"\release-1.7.0.zip"
$webclient.DownloadFile($url, $dlfilename)

# Unzip to test directory
$shellapp = New-Object -ComObject shell.application
$zipfile = $shellapp.namespace($dlfilename)
$destination = $shellapp.namespace($PSScriptRoot);
$files = $zipfile.items()
$destination.Copyhere($files)

# Rename directory
Rename-Item $PSScriptRoot"\googletest-release-1.7.0" "googletest"