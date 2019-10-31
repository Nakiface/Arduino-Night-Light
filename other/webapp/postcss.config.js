const production = !process.env.ROLLUP_WATCH;
const purgecss = require("@fullhuman/postcss-purgecss");

module.exports = {
  plugins: [
    require("postcss-import")(),
    require('precss'),
    require("tailwindcss"),
    require('rucksack-css'),
    require('postcss-hocus'),
    require("autoprefixer"),
    production && purgecss({
    content: ["./**/*.html", "./**/*.svelte"],
    defaultExtractor: content => content.match(/[A-Za-z0-9-_:/]+/g) || []
    }),
    require('cssnano')
  ]
};