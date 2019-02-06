open Types;
open DbTypes;

let widgetStore = ref(Data.widgetStore);
let userStore = ref(Data.userStore);

module FakeDb = {
  let connection = Fake;

  let connect = (_: string): future(connection) => fresolve(Fake);

  let login = (userName: string, passHash: string): future(userRecord_t) => {
    let maybeUser = StrMap.get(userStore^, userName);
    switch (maybeUser) {
    | Some(user) =>
      if (user.passHash == passHash) {
        fresolve(user);
      } else {
        freject("Invalid credentials");
      }
    | None => freject("Invalid credentials")
    };
  };

  let findWidget = (id: string): future(widgetRecord_t) => {
    let match = StrMap.get(widgetStore^, id);
    switch (match) {
    | Some(devce) => fresolve(devce)
    | None => freject("Not found")
    };
  };

  let addWidget = (widget: widgetRecord_t): future(widgetRecord_t) => {
    widgetStore := StrMap.set(widgetStore^, widget.id, widget);
    fresolve(widget);
  };
};