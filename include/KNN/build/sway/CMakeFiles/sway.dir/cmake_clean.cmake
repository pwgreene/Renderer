file(REMOVE_RECURSE
  "libsway.pdb"
  "libsway.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sway.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
