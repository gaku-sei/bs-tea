open Tea;

[@bs.deriving accessors]
type msg =
  | CategoriesNoop
  | SetSearch(string, string);

type model = {count: int};

let update = (model, msg) =>
  switch (msg) {
  | CategoriesNoop
  | SetSearch(_) => ({count: model.count + 1}, Cmd.none)
  };

let view = ({count}) =>
  Html.(
    div(
      [],
      [
        div([], [text(string_of_int(count))]),
        table(
          [class'("uk-table uk-table-striped")],
          [
            thead(
              [],
              [
                tr(
                  [],
                  [
                    th([onClick(SetSearch("id", "asc"))], [text("Id")]),
                    th(
                      [onClick(SetSearch("title", "asc"))],
                      [text("Title")],
                    ),
                    th(
                      [onClick(SetSearch("url", "asc"))],
                      [text("Url")],
                    ),
                  ],
                ),
              ],
            ),
            tbody(
              [],
              [
                tr(
                  [],
                  [
                    td([], [text("1")]),
                    td([], [text("Super title")]),
                    td([], [text("https://www.abc.fr")]),
                  ],
                ),
                tr(
                  [],
                  [
                    td([], [text("2")]),
                    td([], [text("Title")]),
                    td([], [text("https://www.fff.fr")]),
                  ],
                ),
                tr(
                  [],
                  [
                    td([], [text("3")]),
                    td([], [text("Mega title")]),
                    td([], [text("https://www.zyx.fr")]),
                  ],
                ),
              ],
            ),
          ],
        ),
      ],
    )
  );