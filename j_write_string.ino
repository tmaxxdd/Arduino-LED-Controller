char* rmvstr(char str[], char toRemove[], char *result){
    byte needed = strlen(str) - strlen(toRemove);
    for (int i = 0; i < needed; i++) {
      result[i] = str[strlen(toRemove) + i];
    }
    // Add string termination letter
    result[needed] = '\0';
    return result;
}
