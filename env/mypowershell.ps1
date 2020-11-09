# can source with . like in bash:
# https://superuser.com/questions/71446/equivalent-of-bashs-source-command-in-powershell

# something like 'dir /od' or 'ls -ltr'
function ld 
{
    Get-ChildItem | sort-object -Property LastWriteTime	
}
