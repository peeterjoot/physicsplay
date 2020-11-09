
#$env:PATH = 
#";C:\Program Files (x86)\Vim\vim73" + `
#";C:\cygwin\bin" + `
#";$env:PATH"

# No point putting this in the profile.  Have to execute SetEnv.Cmd externally from powershell for all the vars.
##";C:\Program Files\Microsoft SDKs\Windows\v7.0\Bin\x64" + `
##

#function homedir {set-location -path $env:HOMEPATH}

function vim
{
	C:\"Program Files (x86)"\Vim\vim82\vim.exe $args
}

function eprofile
{
	vim \\wsl$\Ubuntu\home\pjoot\physicsplay\env\profile_powershell.ps1
}

#function mdir {set-location -path ~/cygwin_home/physicsplay}
#function jdir {set-location -path ~/cygwin_home/physicsplay/gaJuliaFractal}
#function e2dir {set-location -path C:\Users\Peeter\cygwin_home\gasand\ga25\TestG25\e2ga_cpp}

#Remove-item Alias:cd
#function cd
#{
#	if ($args[0] -eq '-')
#	{
#		$pwd = $OLDPWD ;
#	}
#	else
#	{
#		$pwd = $args[0] ;
#	}
#	
#	$tmp = pwd ;
#	
#	if ( $pwd )
#	{
#		Set-Location $pwd ;
#	}
#	
#	Set-Variable -Name OLDPWD -Value $tmp -Scope global  ;
#}

# can source with . like in bash:
# https://superuser.com/questions/71446/equivalent-of-bashs-source-command-in-powershell

# something like 'dir /od' or 'ls -ltr'
function ld 
{
    Get-ChildItem | sort-object -Property LastWriteTime	
}
