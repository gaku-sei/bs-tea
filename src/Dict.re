include Js.Dict;

let safeSet: (t('a), key, 'a) => t('a) =
  (dict, key, value) =>
    entries(dict)->Js.Array.concat([|(key, value)|]) |> fromArray;