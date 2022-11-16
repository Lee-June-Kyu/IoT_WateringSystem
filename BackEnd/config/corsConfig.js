const whitelist = require('./whiteList.json');

// const CorsConfig = {
//   origin: Array < string >;
//   methods: Array < string >;
//   credentials: boolean;
// };

const corsConfig = {
  origin: whitelist,
  methods: ['OPTIONS', 'GET', 'POST', 'HEAD', 'PATCH', 'DELETE'],
  credentials: true,
};

module.exports = corsConfig;
// export default corsConfig;

// "_comment": "http://localhost:8080",