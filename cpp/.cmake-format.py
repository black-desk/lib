# ----------------------------------
# Options affecting listfile parsing
# ----------------------------------
with section("parse"):

  # Specify structure for custom cmake functions
  additional_commands = { 'cpmaddpackage': { 'kwargs': { 'DOWNLOAD_COMMAND': 1,
                                   'DOWNLOAD_NAME': 1,
                                   'DOWNLOAD_NO_EXTRACT': 1,
                                   'DOWNLOAD_ONLY': 1,
                                   'EXCLUDE_FROM_ALL': 1,
                                   'FIND_PACKAGE_ARGUMENTS': 1,
                                   'FORCE': 1,
                                   'GITHUB_REPOSITORY': 1,
                                   'GITLAB_REPOSITORY': 1,
                                   'GIT_REPOSITORY': 1,
                                   'GIT_SHALLOW': 1,
                                   'GIT_TAG': 1,
                                   'HTTP_PASSWORD': 1,
                                   'HTTP_USERNAME': 1,
                                   'NAME': 1,
                                   'NO_CACHE': 1,
                                   'OPTIONS': '+',
                                   'SOURCE_DIR': 1,
                                   'SOURCE_SUBDIR': 1,
                                   'SVN_REPOSITORY': 1,
                                   'SVN_REVISION': 1,
                                   'URL': 1,
                                   'URL_HASH': 1,
                                   'URL_MD5': 1,
                                   'VERSION': 1},
                       'pargs': {'flags': [], 'nargs': '*'},
                       'spelling': 'CPMAddPackage'},
    'cpmdeclarepackage': { 'kwargs': { 'DOWNLOAD_COMMAND': 1,
                                       'DOWNLOAD_NAME': 1,
                                       'DOWNLOAD_NO_EXTRACT': 1,
                                       'DOWNLOAD_ONLY': 1,
                                       'EXCLUDE_FROM_ALL': 1,
                                       'FIND_PACKAGE_ARGUMENTS': 1,
                                       'FORCE': 1,
                                       'GITHUB_REPOSITORY': 1,
                                       'GITLAB_REPOSITORY': 1,
                                       'GIT_REPOSITORY': 1,
                                       'GIT_SHALLOW': 1,
                                       'GIT_TAG': 1,
                                       'HTTP_PASSWORD': 1,
                                       'HTTP_USERNAME': 1,
                                       'NAME': 1,
                                       'NO_CACHE': 1,
                                       'OPTIONS': '+',
                                       'SOURCE_DIR': 1,
                                       'SOURCE_SUBDIR': 1,
                                       'SVN_REPOSITORY': 1,
                                       'SVN_REVISION': 1,
                                       'URL': 1,
                                       'URL_HASH': 1,
                                       'URL_MD5': 1,
                                       'VERSION': 1},
                           'pargs': {'flags': [], 'nargs': '*'},
                           'spelling': 'CPMDeclarePackage'},
    'cpmfindpackage': { 'kwargs': { 'DOWNLOAD_COMMAND': 1,
                                    'DOWNLOAD_NAME': 1,
                                    'DOWNLOAD_NO_EXTRACT': 1,
                                    'DOWNLOAD_ONLY': 1,
                                    'EXCLUDE_FROM_ALL': 1,
                                    'FIND_PACKAGE_ARGUMENTS': 1,
                                    'FORCE': 1,
                                    'GITHUB_REPOSITORY': 1,
                                    'GITLAB_REPOSITORY': 1,
                                    'GIT_REPOSITORY': 1,
                                    'GIT_SHALLOW': 1,
                                    'GIT_TAG': 1,
                                    'HTTP_PASSWORD': 1,
                                    'HTTP_USERNAME': 1,
                                    'NAME': 1,
                                    'NO_CACHE': 1,
                                    'OPTIONS': '+',
                                    'SOURCE_DIR': 1,
                                    'SOURCE_SUBDIR': 1,
                                    'SVN_REPOSITORY': 1,
                                    'SVN_REVISION': 1,
                                    'URL': 1,
                                    'URL_HASH': 1,
                                    'URL_MD5': 1,
                                    'VERSION': 1},
                        'pargs': {'flags': [], 'nargs': '*'},
                        'spelling': 'CPMFindPackage'},
    'cpmgetpackageversion': {'pargs': 2, 'spelling': 'CPMGetPackageVersion'},
    'cpmregisterpackage': {'pargs': 1, 'spelling': 'CPMRegisterPackage'},
    'cpmusepackagelock': {'pargs': 1, 'spelling': 'CPMUsePackageLock'},
    'packageproject': { 'kwargs': { 'BINARY_DIR': 1,
                                    'COMPATIBILITY': 1,
                                    'DEPENDENCIES': '+',
                                    'INCLUDE_DESTINATION': 1,
                                    'INCLUDE_DIR': 1,
                                    'NAME': 1,
                                    'VERSION': 1,
                                    'VERSION_HEADER': 1},
                        'pargs': {'flags': [], 'nargs': '*'},
                        'spelling': 'packageProject'}}

# -----------------------------
# Options affecting formatting.
# -----------------------------
with section("format"):

  # How wide to allow formatted cmake files
  line_width = 100

  # How many spaces to tab for indent
  tab_size = 2

  # If a statement is wrapped to more than one line, than dangle the closing
  # parenthesis on its own line.
  dangle_parens = True

