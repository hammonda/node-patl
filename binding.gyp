{
  'targets': [
    {
      'target_name': 'nodepatl',
      'include_dirs': [
        './src',
        './deps'
      ],
      'sources': [
        'src/nodepatl.cpp'
      , 'src/Patl.cpp'
      ],
      'cflags': [
        '-fexceptions'      
      ],
      'cflags_cc': [
        '-O3'
      , '-fexceptions'
      , '-Wall'
      ]
    }
  ]
}
