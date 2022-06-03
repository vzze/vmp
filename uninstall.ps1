if(Test-Path -Path "~/vmp") {
    $path = [System.Environment]::GetEnvironmentVariable(
        "PATH",
        "Machine"
    )

    $remove = Resolve-Path("~/vmp/bin")

    $path = ($path.Split(';') | Where-Object { $_ -ne "$remove" }) -join ';'

    [System.Environment]::SetEnvironmentVariable(
        "PATH",
        $path,
        "Machine"
    )

    Remove-Item -Recurse -Path "~/vmp"
}
