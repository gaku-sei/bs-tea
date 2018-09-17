open Json;

[@bs.module "qs"] external queryStringParse: string => Js.Json.t = "parse";

[@bs.module "qs"]
external queryStringStringify: Js.Json.t => string = "stringify";

let parse = value => queryStringParse(value) |> Decode.(dict(string));

let stringify = value =>
  Encode.(
    value
    |> Js.Dict.map((. value) => string(value))
    |> dict
    |> queryStringStringify
  );