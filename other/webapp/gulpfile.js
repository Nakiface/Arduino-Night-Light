const gulp = require("gulp");



gulp.task('css', () => {
    const postcss = require('gulp-postcss')

    const purgecss = require('@fullhuman/postcss-purgecss')({

        // Specify the paths to all of the template files in your project 
        content: [
            './*.html'
        ],

        // Include any special characters you're using in this regular expression
        defaultExtractor: content => content.match(/[\w-/:]+(?<!:)/g) || []
    })

    return gulp.src('*.css')
        .pipe(postcss([
            require('precss'),
            require('tailwindcss'),
            require('autoprefixer'),
            purgecss,
            require('cssnano')
        ]))
        .pipe(gulp.dest('build/'))
})