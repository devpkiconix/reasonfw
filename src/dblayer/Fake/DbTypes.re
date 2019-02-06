/* module StrModule = Belt.Map.String; */

type connection =
  | Fake
  | MySql(string);

/* DB record */
type widgetRecord_t = {
  id: string,
  name: string,
};
/* DB record */
type userRecord_t = {
  id: string,
  email: string,
  username: string,
  passHash: string,
  accessToken: string,
};

module StrMap = Belt.Map.String;
type widgetStore_t = StrMap.t(widgetRecord_t);
type groupStore_t = StrMap.t(list(Types.id_t));
type userStore_t = StrMap.t(userRecord_t);