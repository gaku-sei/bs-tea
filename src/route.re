open Belt;

type route =
  | Home
  | Categories;

let locationToRoute: Web.Location.location => route =
  location =>
    switch (
      location.pathname
      |> Js.String.split("/")
      |> List.fromArray
      |> List.tailExn
    ) {
    | [] => Home
    | ["categories"] => Categories
    | _ => Home
    | exception _ => Home
    };

let routeToPath: route => string =
  fun
  | Home => "/"
  | Categories => "/categories";