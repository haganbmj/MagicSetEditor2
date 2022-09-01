project = 'MagicSetEditor2'

version = '2.3.1'
release = '2.3.1'

html_logo = 'logo.png'

html_theme = 'sphinx_rtd_theme'
html_theme_options = {
    'collapse_navigation': False,
    'style_external_links': True,
    'prev_next_buttons_location': 'both',
    'style_nav_header_background': '#2175bc',
}

extensions = [
    'sphinx.ext.autosectionlabel',
]

# html_static_path = ['_static']
# html_css_files = [
#     'css/custom.css'
# ]
# html_js_files = [
#     'js/custom.js'
# ]

# Trying to use a dummy lanaguage to test highlighting.
# It looks like it'll be possible to define a custom Lexer language type...
highlight_language = 'julia'
pygments_style = 'monokai'
