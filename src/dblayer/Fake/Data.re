open DbTypes;

let widgetStore: widgetStore_t =
  StrMap.fromArray([||])
  ->StrMap.set("id1", {id: "id1", name: "firstwidget"})
  ->StrMap.set("id2", {id: "id2", name: "secondwidget"});

let userStore: userStore_t =
  StrMap.fromArray([||])
  ->StrMap.set(
      "user1",
      {
        id: "1",
        email: "user1@example.com",
        username: "user1",
        passHash: "1234",
        accessToken: "token1",
      },
    )
  ->StrMap.set(
      "user2",
      {
        id: "2",
        email: "user2@example.com",
        username: "user2",
        passHash: "1234",
        accessToken: "token2",
      },
    );