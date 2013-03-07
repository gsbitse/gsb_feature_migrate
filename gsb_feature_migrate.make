; GSB Feature Migrate

api = 2
core = 7.x

; Feeds migration modules.

projects[feeds_crawler][version] = 1.x-dev
projects[feeds_crawler][subdir] = contrib

projects[feeds_files][version] = 1.x-dev
projects[feeds_files][subdir] = contrib
projects[feeds_files][download][type] = git
projects[feeds_files][download][revision] = 22c1ad1
projects[feeds_files][download][branch] = 7.x-1.x
projects[feeds_files][patch][feeds_files-existing-fid-by-uri-fix] = https://raw.github.com/gsbitse/gsb-revamp-patches/master/feeds_files-existing-fid-by-uri-fix.patch
