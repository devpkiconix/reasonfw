let dummyCheck = (accessToken: string) => accessToken == "token1";
let isSuperAdmin = dummyCheck;
let isFwAdmin = dummyCheck;
let isLicenseAdmin = dummyCheck;
let isAppStoreAdmin = dummyCheck;
let isConfigAdmin = dummyCheck;

let isValidToken = (accessToken: string) =>
  accessToken == "token1" || accessToken == "token2";