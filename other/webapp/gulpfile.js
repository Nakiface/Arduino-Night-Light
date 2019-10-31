const gulp = require('gulp')

gulp.task('copy', () => {
    return gulp.src('./public/*.{html,css,js,png}')
        .pipe(gulp.dest('../../data'))
})