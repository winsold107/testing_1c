from django.conf.urls import include, url
from django.contrib import admin
from django.conf import settings

urlpatterns = [

    url(r'^', include('balda_game.urls')),
    url(r'^admin/', include(admin.site.urls)),
]

if settings.DEBUG:  # add this part at the buttom of the urls.py
    import debug_toolbar
    urlpatterns = [
        url(r'^__debug__/', include(debug_toolbar.urls)),
    ] + urlpatterns
