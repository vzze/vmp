if(!(Test-Path -Path "~/vmp")) {
    New-Item -Path "~/vmp" -ItemType "directory"
    New-Item -Path "~/vmp/Songs" -ItemType "directory"
    New-Item -Path "~/vmp/Queues" -ItemType "directory"
    New-Item -Path "~/vmp/bin" -ItemType "directory"
}

Copy-Item -Path "./bin/vmp.exe" -Destination "~/vmp/bin"

$path = Resolve-Path("~/vmp/bin")

if(!$env:Path.Contains(";~/Desktop/vmp/bin")) {
    [System.Environment]::SetEnvironmentVariable("PATH", $env:Path + ";$path", "Machine")
}
