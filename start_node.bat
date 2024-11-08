@echo off

set JenkinsPath="C:\Jenkins"

cd %JenkinsPath%

curl.exe -sO http://localhost:8080/jnlpJars/agent.jar & java -jar agent.jar -url http://localhost:8080/ -secret 1c5c6f48f80e25bf96dec611c2b4545b541877f316055b0d45025af4af8ed942 -name "hichigo_node1" -webSocket -workDir "C:\Jenkins"