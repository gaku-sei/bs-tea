open Tea;

[@bs.deriving accessors]
type msg =
  | LocationChanged(Web.Location.location)
  | Noop
  | CategoriesMsg(Categories.msg);

type model = {
  categoriesModel: Categories.model,
  location: Web.Location.location,
};

let init = ((), location) => (
  {
    categoriesModel: {
      count: 0,
    },
    location,
  },
  Cmd.none,
);

let shutdown = _ => Cmd.none;

let subscriptions = _ => Sub.none;

let update = ({location: {hash, pathname, search}} as model) =>
  fun
  | LocationChanged(location) => ({...model, location}, Cmd.none)
  | Noop => (model, Cmd.none)
  | CategoriesMsg(SetSearch(key, value) as msg) => {
      let (categoriesModel, cmd) =
        Categories.update(model.categoriesModel, msg);
      let newSearch =
        (search |> Js.String.sliceToEnd(~from=1) |> QueryString.parse)
        ->Dict.safeSet(key, value)
        |> QueryString.stringify;
      (
        {...model, categoriesModel},
        Cmd.batch([cmd, Navigation.newUrl({j|$pathname?$newSearch$hash|j})]),
      );
    }
  | CategoriesMsg(msg) => {
      let (categoriesModel, cmd) =
        Categories.update(model.categoriesModel, msg);
      ({...model, categoriesModel}, cmd);
    };

let home = _ => Html.(div([], [text("Home!")]));

let view = ({location} as model) =>
  Html.(
    div(
      [],
      [
        a([href(Route.routeToPath(Home))], [text("Home")]),
        a([href(Route.routeToPath(Categories))], [text("Categories")]),
        div(
          [],
          [
            switch (Route.locationToRoute(location)) {
            | Home => home(model)
            | Categories =>
              App.map(categoriesMsg, Categories.view(model.categoriesModel))
            },
          ],
        ),
      ],
    )
  );

let main =
  Navigation.navigationProgram(
    locationChanged,
    {init, shutdown, subscriptions, update, view},
  );