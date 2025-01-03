{%- comment -%}
//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//
{%- endcomment -%}

{%- comment -%}
//
// This file should roughly mirror the doc/readme/source_code.adoc file.
// If you edit this file, you might need to edit that file as well.
//
{%- endcomment -%}

## Source code

{% assign fp_artifact = "source code" %}
{% assign fp_builtin_view_latest_url = "" %}
{% assign fp_builtin_view_pinned_url = "" %}
{% assign fp_builtin_download_latest_url = "" %}
{% assign fp_builtin_download_pinned_url = "" %}
{% assign fp_github_view_latest_url = "https://github.com/stealthsoftwareinc/" | append: PACKAGE_TARNAME | append: "/tree/master" %}
{% assign fp_github_view_pinned_url = "" %}
{% assign fp_github_download_latest_url = "https://github.com/stealthsoftwareinc/" | append: PACKAGE_TARNAME | append: "/archive/refs/heads/master.tar.gz" %}
{% assign fp_github_download_pinned_url = "" %}
{% assign fp_gitlab_view_latest_url = "" %}
{% assign fp_gitlab_view_pinned_url = "" %}
{% assign fp_gitlab_download_latest_url = "" %}
{% assign fp_gitlab_download_pinned_url = "" %}
{% assign fp_devel_view_latest_url = "https://gitlab.stealthsoftwareinc.com/stealth/" | append: PACKAGE_TARNAME | append: "/-/tree/master" %}
{% assign fp_devel_view_pinned_url = "" %}
{% assign fp_devel_download_latest_url = "" %}
{% assign fp_devel_download_pinned_url = "" %}
{% unless in_source_repo %}
{% assign fp_github_download_pinned_url = "https://github.com/stealthsoftwareinc/" | append: PACKAGE_TARNAME | append: "/raw/v" | append: PACKAGE_VERSION | append: "/" | append: PACKAGE_TARNAME | append: "-" | append: PACKAGE_VERSION | append: ".tar.gz" %}
{% endunless %}

{% include artifact_links_fragment.md %}
