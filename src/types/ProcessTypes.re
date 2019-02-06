/* Type definitions for process related functions */
type privilegedRequest_t('p) = {
  accessToken: string,
  payload: 'p,
};