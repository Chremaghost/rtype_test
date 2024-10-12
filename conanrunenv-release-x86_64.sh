script_folder="/home/chrema/B-CPP-500-COT-5-1-rtype-yann-meric.sossou"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in ALSA_CONFIG_DIR
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export ALSA_CONFIG_DIR="/home/chrema/.conan2/p/b/libala6e3be6abb022/p/res/alsa"