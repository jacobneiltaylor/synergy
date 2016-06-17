# Download source if not already available
if((Test-Path $PSScriptRoot"\googletest") -eq $false)
{
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
}

# Enter directory and create build directories
cd $PSScriptRoot"\googletest"

Remove-Item -Recurse -Force ./x64
Remove-Item -Recurse -Force ./x86
Remove-Item -Recurse -Force ./msbuild

mkdir ./x64
mkdir ./x86
mkdir ./msbuild

# Load msbuild module
cd ./msbuild

$webclient = New-Object System.Net.WebClient
$url = "https://github.com/deadlydog/Invoke-MsBuild/releases/download/v2.0.0/Invoke-MsBuild.psm1"
$dlfilename = $PSScriptRoot + "\googletest\msbuild\Invoke-MsBuild.psm1"
$webclient.DownloadFile($url, $dlfilename)

Import-Module $PSScriptRoot"\googletest\msbuild\Invoke-MsBuild.psm1"

cd ..

# Reset PATH
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")

# Build 32bit
Write-Host "Beginning build: GoogleTest (32bit)"

cd x86

cmake -G "Visual Studio 14 2015" ../

if ((Invoke-MsBuild -Path $PSScriptRoot"\googletest\x86\gtest.sln" -MsBuildParameters "/property:Configuration=Release;Platform=Win32").BuildSucceeded -eq $true)
{
    Write-Host "Build succeeded for GoogleTest (32bit)"
}
else
{
    Write-Host "Build failed for GoogleTest (32bit)"
}


cd ..

# Build 64bit
Write-Host "Beginning build: GoogleTest (64bit)"

cd x64

cmake -G "Visual Studio 14 2015 Win64" ../

if((Invoke-MsBuild -Path $PSScriptRoot"\googletest\x64\gtest.sln" -MsBuildParameters "/property:Configuration=Release;Platform=x64").BuildSucceeded -eq $true)
{
    Write-Host "Build succeeded for GoogleTest (64bit)"
}
else
{
    Write-Host "Build failed for GoogleTest (64bit)"
}

cd ../..