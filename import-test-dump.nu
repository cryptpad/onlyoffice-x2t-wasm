#!/usr/bin/env -S nu --stdin

def main [
  target: path
] {
  let data = $in
  let parsed = $data | from json
  $parsed | each {|x|
    let path = $x.path | str replace -r '^/' ''
    let savePath = $target | path join $path
    print $savePath
    mkdir ($savePath | path dirname)
    let data = $x.content | decode base64
    $data | save --raw $savePath
  }
}
