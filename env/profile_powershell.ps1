
$env:PATH = 
";C:\Program Files (x86)\Vim\vim73" + `
";C:\cygwin\bin" + `
"$env:PATH"

# No point putting this in the profile.  Have to execute SetEnv.Cmd externally from powershell for all the vars.
##";C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin\x64" + `
##

function homedir {set-location -path $env:HOMEPATH}
